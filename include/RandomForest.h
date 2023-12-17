//
// Created by adrien on 12/17/23.
//

#ifndef CLASSIFICATIONTP_RANDOMFOREST_H
#define CLASSIFICATIONTP_RANDOMFOREST_H

#include "DecisionTree.h"

typedef struct sRandomForest{
    DecisionTreeNode** trees;
    int treeCount;
    int classCount;
} RandomForest;
#endif //CLASSIFICATIONTP_RANDOMFOREST_H

/**
 * @brief Create a Random Forest ensemble based on bagging and decision tree creation.
 *
 * This function creates a Random Forest ensemble by generating multiple decision trees.
 * Each tree is trained on a subset of the original dataset, obtained through bagging
 * (Bootstrap Aggregating), to enhance diversity in the ensemble.
 *
 * @param numberOfTrees The number of decision trees in the Random Forest.
 * @param data A pointer to the original dataset for training the decision trees.
 * @param maxDepth The maximum depth allowed for each decision tree in the ensemble.
 * @param baggingProportion The proportion of the dataset to be used for bagging each tree.
 * @param prunningThreshold The pruning threshold for decision tree construction.
 * @return A pointer to the created Random Forest ensemble.
 */
RandomForest *RandomForest_create(
        int numberOfTrees,
        Dataset *data,
        int maxDepth,
        float baggingProportion,
        float prunningThreshold);

/**
 * @brief Create a subproblem by performing bagging on a dataset.
 *
 * Bagging (Bootstrap Aggregating) is a technique that involves creating multiple
 * subsets (bags) of a dataset by randomly sampling with replacement. This function
 * creates a subproblem by performing bagging on a given dataset.
 *
 * @param data A pointer to the dataset to be used for bagging.
 * @param proportion The proportion of the dataset to be used for bagging (0.0 to 1.0).
 * @return A pointer to the created subproblem containing the bagged instances.
 */
Subproblem *Dataset_bagging(Dataset *data, float proportion);

/**
 * @brief Predict the class label for a given instance using a Random Forest.
 *
 * This function predicts the class label for a given instance using an ensemble of
 * decision trees in a Random Forest. It counts the votes from each decision tree and
 * returns the class label that receives the most votes.
 *
 * @param rf A pointer to the Random Forest structure.
 * @param instance A pointer to the instance for which the class label is to be predicted.
 * @return The predicted class label for the given instance.
 */
int RandomForest_predict(RandomForest *rf, Instance *instance);

/**
 * @brief Evaluate the accuracy of a Random Forest on a dataset.
 *
 * This function takes a Random Forest and a dataset as input and evaluates the accuracy
 * of the Random Forest on the given dataset by comparing the predicted class labels
 * with the actual class labels in the dataset.
 *
 * @param rf A pointer to the Random Forest structure.
 * @param data A pointer to the dataset containing instances for evaluation.
 * @return The accuracy of the Random Forest on the dataset, represented as a floating-point
 *         value between 0.0 and 1.0 (0% to 100% accuracy).
 */
float RandomForest_evaluate(RandomForest *rf, Dataset *data);

/**
 * @brief Count the total number of nodes in all decision trees of a Random Forest.
 *
 * This function calculates and returns the total number of nodes across all decision
 * trees in a Random Forest. It provides an indication of the complexity of the ensemble
 * of decision trees.
 *
 * @param rf A pointer to the Random Forest structure.
 * @return The total number of nodes in all decision trees of the Random Forest.
 */
int RandomForest_nodeCount(RandomForest *rf);

/**
 * @brief Deallocate memory used by a Random Forest and its decision trees.
 *
 * This function frees the memory allocated for a Random Forest and its individual
 * decision trees. It should be called to prevent memory leaks when the Random Forest
 * is no longer needed.
 *
 * @param rf A pointer to the Random Forest structure to be destroyed.
 */
void RandomForest_destroy(RandomForest *rf);