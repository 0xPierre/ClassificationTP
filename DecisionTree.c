#include "Settings.h"


//float calculate_purity(Subproblem* sp) {
//	int countLeft = 
//}

DecisionTreeNode* DecisionTree_create(Subproblem* sp, int currentDepth, int maxDepth, float prunningThreshold)
{
	// Si la profondeur est atteinte
	if (currentDepth == maxDepth) {
		printf("Max depth reached\n");
		return NULL;
	}

	DecisionTreeNode* node = (DecisionTreeNode*)calloc(1, sizeof(DecisionTreeNode));
	if (node == NULL) {
		printf("DecisionTreeNode Memory allocation failed - node\n");
		return NULL;
	}

	// Recherche de la classe majoritaire de sp
	int majority_class_count = 0;

	for (int c = 0; c < sp->classCount; c++)
	{
		if (sp->classes[c].instanceCount > majority_class_count) {
			majority_class_count = sp->classes[c].instanceCount;
			node->classID = c;
		}
	}

	float purity = (float)majority_class_count / (float)sp->instanceCount;

	// Si la purete est supérieut à prunningThreshold
	if (purity >= prunningThreshold) {
		// On retourne un noeud avec la classe majoritaire
		return node;
	}

	// La purete est inférieure à prunningThreshold
	// On calcule le split
	node->split = Split_compute(sp);

	// On crée les sous-problèmes
	Subproblem* leftSubproblem = Subproblem_create(sp->instanceCount, sp->featureCount, sp->classCount);
	Subproblem* rightSubproblem = Subproblem_create(sp->instanceCount, sp->featureCount, sp->classCount);

	if (leftSubproblem == NULL || rightSubproblem == NULL) {
		printf("Subproblem Memory allocation failed - left or right Subproblem\n");
		return NULL;
	}

	// Division des instances en fonction du seuil
	for (int i = 0; i < sp->instanceCount; i++) {
		Instance* instance = sp->instances[i];
		if (instance->values[node->split.featureID] <= node->split.threshold) {
			Subproblem_insert(leftSubproblem, instance);
		}
		else {
			Subproblem_insert(rightSubproblem, instance);
		}
	}

	// On crée les noeuds fils
	node->left = DecisionTree_create(leftSubproblem, currentDepth + 1, maxDepth, prunningThreshold);
	node->right = DecisionTree_create(rightSubproblem, currentDepth + 1, maxDepth, prunningThreshold);

	return node;
}

void DecisionTree_destroy(DecisionTreeNode* decisionTree)
{
	if (decisionTree == NULL) {
		return;
	}
	DecisionTree_destroy(decisionTree->left);
	DecisionTree_destroy(decisionTree->right);
	free(decisionTree);
}

int Decision_nodeCount(DecisionTreeNode* decisionTree)
{
	if (decisionTree == NULL) {
		return 0;
	}
	return 1 + Decision_nodeCount(decisionTree->left) + Decision_nodeCount(decisionTree->right);
}