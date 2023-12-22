#include "Settings.h"

typedef struct sDecisionTreeNode {
    struct sDecisionTreeNode *left;
    struct sDecisionTreeNode *right;
    Split split;
    int classID;
} DecisionTreeNode;

DecisionTreeNode *DecisionTree_create(
        Subproblem *sp,
        int currentDepth,
        int maxDepth,
        float prunningThreshold,
        bool *authorizedFeatures
);

void DecisionTree_destroy(DecisionTreeNode *decisionTree);

int Decision_nodeCount(DecisionTreeNode *node);

float sigmoid(int x, float threshold);

void DecisionTree_predict(DecisionTreeNode *tree, Instance *instance, float *tab, float scores);

float DecisionTree_evaluate(DecisionTreeNode *tree, Dataset *dataset);