#include "Settings.h"

typedef struct sRandomForest {
	DecisionTreeNode** trees;
	int treeCount;
	int classCount;
} RandomForest;

Subproblem* Dataset_bagging(Dataset* data, float proportion);

RandomForest* RandomForest_create(
	int numberOfTrees,
	Dataset* data,
	int maxDepth,
	float baggingProportion,
	float prunningThreshold
);

int RandomForest_predict(RandomForest* rf, Instance* instance);

float RandomForest_evaluate(RandomForest* rf, Dataset* data);

int RandomForest_nodeCount(RandomForest* rf);

void RandomForest_destroy(RandomForest* rf);

/*
Return a list of authorized features for the bagging
*/
bool* Dataset_FeatureBagging(Dataset* data, float proportion);