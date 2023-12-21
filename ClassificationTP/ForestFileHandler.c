#include "Settings.h"

void DumpNodeInFile(FILE *file, DecisionTreeNode* node) {
	if (node == NULL) {
		fprintf(file, "-1 -1 -1\n");
		return;
	}
	fprintf(file, "%d %d %f\n", node->classID, node->split.featureID, node->split.threshold);

	DumpNodeInFile(file, node->left);
	DumpNodeInFile(file, node->right);
}

DecisionTreeNode* LoadNodeFromFile(FILE* file) {
	int classID, featureID;
	float threshold;

	if (fscanf(file, "%d %d %f\n", &classID, &featureID, &threshold) == 3) {
		if (classID == -1 && featureID == -1) return NULL;

		DecisionTreeNode* node = calloc(1, sizeof(DecisionTreeNode));
		AssertNew(node);

		node->classID = classID;
		node->split.featureID = featureID;
		node->split.threshold = threshold;

		node->left = LoadNodeFromFile(file);
		node->right = LoadNodeFromFile(file);

		return node;
	}

	return NULL;
}

void ForestFileDump(RandomForest* rf, char path[128]) {
	FILE* file = fopen(path, "w");

	printf("Saving file %s\n", path);

	// Sauvegarde du nombre d'arbre et du nombre de class dans la forêt
	fprintf(file, "%d %d\n", rf->treeCount, rf->classCount);

	// Sauvegarde de chaque arbre
	for (int i = 0; i < rf->treeCount; i++) {
		// Root de chaque arbre
		DecisionTreeNode* tree = rf->trees[i];
		// Enregistre le nombre de node de l'arbre
		fprintf(file, "%d\n", Decision_nodeCount(tree));
		DumpNodeInFile(file, tree);
		// e = end of tree
		fprintf(file, "e\n");
	}

	fclose(file);
}


RandomForest* LoadForestFromFile(char path[128]) {
	printf("Opening file %s\n", path);
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Erreur opening file\n");
		assert(false);
	}

	RandomForest* rf = (RandomForest*)calloc(1, sizeof(RandomForest));
	AssertNew(rf);
	if (fscanf(file, "%d %d", &rf->treeCount, &rf->classCount) != 2) assert(false);

	rf->trees = (DecisionTreeNode**)calloc(rf->treeCount, sizeof(DecisionTreeNode*));
	AssertNew(rf->trees);


	for (int i = 0; i < rf->treeCount; i++) {
		int nodeCount = 0;
		if (fscanf(file, "%d", &nodeCount) != 1) assert(false);

		DecisionTreeNode *tree = LoadNodeFromFile(file);
		//printf("%d nc\n", Decision_nodeCount(tree));

		char endOfTree;
		if (fscanf(file, "%c", &endOfTree) != 1) assert(false);
		if (endOfTree != 'e') assert(false);

		rf->trees[i] = tree;
	}


	return rf;
}