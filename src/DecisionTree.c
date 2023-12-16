//
// Created by adrien on 12/16/23.
//

#include "../include/DecisionTree.h"
#include "stdlib.h"

DecisionTreeNode *DecisionTree_create(
        Subproblem *sp,
        int currentDepth,
        int maxDepth,
        float prunningThreshold) {

    if (currentDepth >= maxDepth) {
        return NULL;
    }

    DecisionTreeNode *node = (DecisionTreeNode *) calloc(1, sizeof(DecisionTreeNode));

    if (Tree_purity(sp).threshold >= prunningThreshold) {
        node->classID = Tree_purity(sp).classID;
        return node;
    }

    node->split = Split_compute(sp);

    Subproblem *subProblemLeft = Subproblem_create(sp->instanceCount, sp->featureCount, sp->classCount);
    Subproblem *subProblemRight = Subproblem_create(sp->instanceCount, sp->featureCount, sp->classCount);


    for (int i = 0; i < sp->instanceCount; i++) {
        Instance *instance = sp->instances[i];
        if ((float) instance->values[node->split.featureID] < node->split.threshold) {
            Subproblem_insert(subProblemLeft, instance);
        } else {
            Subproblem_insert(subProblemRight, instance);
        }
    }

    node->left = DecisionTree_create(subProblemLeft, currentDepth + 1, maxDepth, prunningThreshold);
    node->right = DecisionTree_create(subProblemRight, currentDepth + 1, maxDepth, prunningThreshold);

    Subproblem_destroy(subProblemLeft);
    Subproblem_destroy(subProblemRight);
    return node;
}

TreePurityRes Tree_purity(Subproblem *sp) {
    int maxInstanceCount = 0;
    int index = 0;
    for (int i = 0; i < sp->classCount; ++i) {
        if (sp->classes[i].instanceCount > maxInstanceCount) {
            maxInstanceCount = sp->classes[i].instanceCount;
            index = i;
        }
    }

    TreePurityRes res = {index, (float) maxInstanceCount / (float) sp->instanceCount};

    return res;
}


void DecisionTree_destroy(DecisionTreeNode *decisionTree) {
    if (decisionTree == NULL) {
        return;
    }
    DecisionTree_destroy(decisionTree->left);
    DecisionTree_destroy(decisionTree->right);
    free(decisionTree);
}

int Decision_nodeCount(DecisionTreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + Decision_nodeCount(node->left) + Decision_nodeCount(node->right);
}