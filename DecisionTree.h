#include "Settings.h"

typedef struct sDecisionTreeNode {
	struct sDecisionTreeNode* left;
	struct sDecisionTreeNode* right;
	Split split;
	int classID;
} DecisionTreeNode;

DecisionTreeNode* DecisionTree_create(
	Subproblem* sp,
	int currentDepth,
	int maxDepth,
	float prunningThreshold
);

void DecisionTree_destroy(DecisionTreeNode* decisionTree);

int Decision_nodeCount(DecisionTreeNode* node);