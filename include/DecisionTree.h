//
// Created by adrien on 12/16/23.
//

#ifndef CLASSIFICATIONTP_DECISIONTREE_H
#define CLASSIFICATIONTP_DECISIONTREE_H

#include "Split.h"

typedef struct sDecisionTreeNode{
    struct sDecisionTreeNode* left;
    struct sDecisionTreeNode* right;
    Split split;
    int classID;
} DecisionTreeNode;

typedef struct sTreePurityRes{
    int classID;
    float threshold;
} TreePurityRes;

#endif //CLASSIFICATIONTP_DECISIONTREE_H

/**
 * Creates a decision tree node recursively based on the given subproblem and parameters.
 *
 * @param sp                The subproblem for which to create the decision tree node.
 * @param currentDepth      The current depth of the node in the decision tree.
 * @param maxDepth          The maximum depth allowed for the decision tree (stopping criterion).
 * @param prunningThreshold The purity threshold for pruning the tree. If the purity of a subproblem
 *                          exceeds this threshold, the node becomes a leaf node with the majority class.
 * @return                  A pointer to the created decision tree node.
 *                          If the current depth exceeds the maximum depth, NULL is returned (pruning).
 */
DecisionTreeNode* DecisionTree_create(
        Subproblem* sp,
        int currentDepth,
        int maxDepth,
        float prunningThreshold);

/**
 * Computes the purity of a subproblem by determining the dominant class and its relative frequency.
 *
 * @param sp    The subproblem for which to compute the purity.
 * @return      A structure containing the index of the dominant class and its relative frequency.
 *              The relative frequency is the ratio of the number of instances of the dominant class
 *              to the total number of instances in the subproblem.
 */
TreePurityRes Tree_purity(Subproblem *sp);

/**
 * Recursively deallocates memory for a decision tree and its nodes.
 *
 * @param decisionTree   The root node of the decision tree to be destroyed.
 *                      If NULL, no action is taken (base case of recursion).
 */
void DecisionTree_destroy(DecisionTreeNode *decisionTree);

/**
 * Counts the number of nodes in a decision tree, including the root node and its descendants.
 *
 * @param node  The root node of the decision tree for which to count the nodes.
 *              If NULL, the count is zero (base case of recursion).
 * @return      The total number of nodes in the decision tree.
 */
int Decision_nodeCount(DecisionTreeNode* node);