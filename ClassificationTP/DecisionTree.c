#include "Settings.h"

DecisionTreeNode *
DecisionTree_create(Subproblem *sp, int currentDepth, int maxDepth, float prunningThreshold, bool *authorizedFeatures) {
    // Si la profondeur est atteinte
    if (currentDepth == maxDepth) {
//		printf("Max depth reached\n");
        return NULL;
    }

    DecisionTreeNode *node = (DecisionTreeNode *) calloc(1, sizeof(DecisionTreeNode));
    if (node == NULL) {
        printf("DecisionTreeNode Memory allocation failed - node\n");
        return NULL;
    }

    // Recherche de la classe majoritaire de sp
    int majority_class_count = 0;

    for (int c = 0; c < sp->classCount; c++) {
        if (sp->classes[c].instanceCount > majority_class_count) {
            majority_class_count = sp->classes[c].instanceCount;
            node->classID = c;
        }
    }

    float purity = (float) majority_class_count / (float) sp->instanceCount;

    // Si la purete est superieut a prunningThreshold
    if (purity >= prunningThreshold) {
        // On retourne un noeud avec la classe majoritaire
        return node;
    }

    if (sp->instanceCount == 0) {
        return node;
    }
    // La purete est inf�rieure � prunningThreshold
    // On calcule le split
    node->split = Split_compute(sp, authorizedFeatures);

    // On cr�e les sous-probl�mes
    Subproblem *leftSubproblem = Subproblem_create(sp->instanceCount, sp->featureCount, sp->classCount);
    Subproblem *rightSubproblem = Subproblem_create(sp->instanceCount, sp->featureCount, sp->classCount);

    if (leftSubproblem == NULL || rightSubproblem == NULL) {
        printf("Subproblem Memory allocation failed - left or right Subproblem\n");
        return NULL;
    }

    // Division des instances en fonction du seuil
    for (int i = 0; i < sp->instanceCount; i++) {
        Instance *instance = sp->instances[i];
        if (instance->values[node->split.featureID] < node->split.threshold) {
            Subproblem_insert(leftSubproblem, instance);
        } else {
            Subproblem_insert(rightSubproblem, instance);
        }
    }

    // On cr�e les noeuds fils
    node->left = DecisionTree_create(leftSubproblem, currentDepth + 1, maxDepth, prunningThreshold, authorizedFeatures);
    node->right = DecisionTree_create(rightSubproblem, currentDepth + 1, maxDepth, prunningThreshold,
                                      authorizedFeatures);

    Subproblem_destroy(leftSubproblem);
    Subproblem_destroy(rightSubproblem);

    return node;
}

void DecisionTree_destroy(DecisionTreeNode *decisionTree) {
    if (decisionTree == NULL) {
        return;
    }
    DecisionTree_destroy(decisionTree->left);
    DecisionTree_destroy(decisionTree->right);

    free(decisionTree);
}

int Decision_nodeCount(DecisionTreeNode *decisionTree) {
    if (decisionTree == NULL) {
        return 0;
    }
    return 1 + Decision_nodeCount(decisionTree->left) + Decision_nodeCount(decisionTree->right);
}

float sigmoid(int x, float threshold) {
    return (float) (1.0f / (1 + exp(6.0 * (double) (x - threshold))));
}

void DecisionTree_predict(DecisionTreeNode *decisionTree, Instance *instance, float *tab, float scores) {
    float score = sigmoid(instance->values[decisionTree->split.featureID], decisionTree->split.threshold);

    if (decisionTree->left == NULL && decisionTree->right == NULL) {
        tab[decisionTree->classID] += scores;
        return;
    }

    // Continue the descent based on the threshold
    DecisionTree_predict(decisionTree->left, instance, tab, score * scores);
    DecisionTree_predict(decisionTree->right, instance, tab, (1 - score) * scores);
}

int DecisionTree_predict_normal(DecisionTreeNode* decisionTree, Instance* instance)
{
    // Si on est sur une feuille
    if (decisionTree->left == NULL && decisionTree->right == NULL) {
        return decisionTree->classID;
    }

    // Sinon on continue la descente en fonction du seuil
    if (instance->values[decisionTree->split.featureID] < decisionTree->split.threshold) {
        return DecisionTree_predict_normal(decisionTree->left, instance);
    }
    else {
        return DecisionTree_predict_normal(decisionTree->right, instance);
    }
}

float DecisionTree_evaluate(DecisionTreeNode *decisionTree, Dataset *dataset) {
    int correctEvaluation = 0;
    // It�re sur toutes les instances du dataset pour calculer le taux de r�ussite
    for (int i = 0; i < dataset->instanceCount; i++) {
        Instance instance = dataset->instances[i];
        if (Args.enableSigmoid) {
            float *tab = calloc(dataset->classCount, sizeof(float));
            DecisionTree_predict(decisionTree, &instance, tab, 1);
            float max = 0;
            int predictedClassId = 0;
            for (int j = 0; j < dataset->classCount; ++j) {
                if (tab[j] > max) {
                    max = tab[j];
                    predictedClassId = j;
                }
            }
            if (predictedClassId == instance.classID) {
                correctEvaluation++;
            }
            free(tab);
        } else {
            int predictedClassId = DecisionTree_predict_normal(decisionTree, &instance);
            if (predictedClassId == instance.classID) {
                correctEvaluation++;
            }
        }

    }

    return (float) correctEvaluation / (float) dataset->instanceCount;
}
