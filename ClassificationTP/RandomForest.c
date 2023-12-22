#include "Settings.h"

Subproblem *Dataset_bagging(Dataset *data, float proportion) {
    // Calcul de la capacity maximal
    int maximumCapacity = (int) (data->instanceCount * proportion);

    Subproblem *subproblem = Subproblem_create(maximumCapacity, data->featureCount, data->classCount);

    // Insertion d'instances al�atoires dans le sous-probl�me
    for (int i = 0; i < maximumCapacity; i++) {
        //int randomIndex = rand() % data->instanceCount;
        int randomIndex = ((rand() ^ (rand() << 15)) & 0x7FFFFFFF) % data->instanceCount;
        Subproblem_insert(subproblem, &data->instances[randomIndex]);
    }

    return subproblem;
}


bool *Dataset_FeatureBagging(Dataset *data, float proportion) {
    bool *authorizedFeatures = (bool *) calloc(data->featureCount, sizeof(bool));
    AssertNew(authorizedFeatures);

    int authorizedFeaturesCount = (int) (data->featureCount * proportion);

    for (int i = 0; i < authorizedFeaturesCount; i++) {
        int randomIndex = ((rand() ^ (rand() << 15)) & 0x7FFFFFFF) % data->featureCount;
        authorizedFeatures[randomIndex] = true;
    }

    return authorizedFeatures;
}

RandomForest *RandomForest_create(
        int numberOfTrees,
        Dataset *data,
        int maxDepth,
        float baggingProportion,
        float prunningThreshold
) {
    RandomForest *randomForest = (RandomForest *) calloc(1, sizeof(RandomForest));
    if (randomForest == NULL) {
        printf("RandomForest Memory allocation failed - RandomForest_create\n");
        return NULL;
    }

    // Alloue le tableau de pointeurs d'arbres
    randomForest->trees = (DecisionTreeNode **) calloc(numberOfTrees, sizeof(DecisionTreeNode *));
    randomForest->classCount = data->classCount;
    if (randomForest->trees == NULL) {
        printf("RandomForest Memory allocation failed - trees\n");
        return NULL;
    }

    omp_set_dynamic(0);
    omp_set_num_threads(THREADS);

#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < numberOfTrees; i++) {
            if (!Args.isSilent)
                printf("Creating tree %d\n", i);
            Subproblem *subproblem = Dataset_bagging(data, baggingProportion);

            // On récupère les features autorisées pour le bagging
            bool *authorizedFeatures = NULL;
            if (Args.useFeatureBagging) {
                authorizedFeatures = Dataset_FeatureBagging(data, Args.featureBaggingProportion);
            }

            randomForest->trees[i] = DecisionTree_create(subproblem, 0, maxDepth, prunningThreshold,
                                                         authorizedFeatures);
            // On supprime le subproblem généré au dessus
            Subproblem_destroy(subproblem);
#pragma omp atomic
            randomForest->treeCount++;
        }
    }
    return randomForest;
}

int RandomForest_predict(RandomForest *rf, Instance *instance) {
    // Tableau de votes : nombres de vote par index : votes[0] = nombre de vote pour la classe 0
    int *votes = (int *) calloc(rf->classCount, sizeof(int));
    if (votes == NULL) {
        printf("RandomForest Memory allocation failed - votes\n");
        return -1;
    }

    if (Args.enableSigmoid) {
        // Pr�diction pour chacun des arbres
        for (int i = 0; i < rf->treeCount; i++) {
            // La pr�diction renvoie la class
            float *tab = calloc(rf->classCount, sizeof(float));
            DecisionTree_predict(rf->trees[i], instance, tab, 1);

            float max = 0;
            int vote = 0;
            for (int j = 0; j < rf->classCount; ++j) {
                if (tab[j] > max) {
                    max = tab[j];
                    vote = j;
                }
            }

            votes[vote]++;
            free(tab);
        }

        int maxVote = 0;
        int maxClassVote = 0;

        // Recherche de la classe avec le plus de votes
        for (int i = 0; i < rf->classCount; i++) {
            if (votes[i] > maxVote) {
                maxVote = votes[i];
                maxClassVote = i;
            }
        }

        free(votes);

        return maxClassVote;
    } else {
        // Pr�diction pour chacun des arbres
        for (int i = 0; i < rf->treeCount; i++) {
            // La pr�diction renvoie la class
            int vote = DecisionTree_predict_normal(rf->trees[i], instance);
            votes[vote]++;
        }

        int maxVote = 0;
        int maxClassVote = 0;

        // Recherche de la classe avec le plus de votes
        for (int i = 0; i < rf->classCount; i++) {
            if (votes[i] > maxVote) {
                maxVote = votes[i];
                maxClassVote = i;
            }
        }

        free(votes);

        return maxClassVote;
    }

}

float RandomForest_evaluate(RandomForest *rf, Dataset *data) {
    int correctCount = 0;
    // It�re sur toutes les instances du dataset pour calculer le taux de r�ussite
    for (int i = 0; i < data->instanceCount; i++) {
        int prediction = RandomForest_predict(rf, &data->instances[i]);
        if (Args.isInVPL) {
            printf("%d\n", prediction);
        }
        if (prediction == data->instances[i].classID)
            correctCount++;
    }
    return (float) correctCount / (float) data->instanceCount;
}

int RandomForest_nodeCount(RandomForest *rf) {
    int nodeCount = 0;
    // It�re sur tous les arbres pour calculer le nombre de noeuds
    for (int i = 0; i < rf->treeCount; i++) {
        nodeCount += Decision_nodeCount(rf->trees[i]);
    }
    return nodeCount;
}

void RandomForest_destroy(RandomForest *rf) {
    for (int i = 0; i < rf->treeCount; i++) {
        DecisionTree_destroy(rf->trees[i]);
    }
    free(rf->trees);

    free(rf);
}