//
// Created by adrien on 12/17/23.
//

#include "../include/RandomForest.h"
#include "stdlib.h"

RandomForest *RandomForest_create(
        int numberOfTrees,
        Dataset *data,
        int maxDepth,
        float baggingProportion,
        float prunningThreshold) {

    RandomForest *forest = calloc(1, sizeof(RandomForest));
    forest->trees = calloc(numberOfTrees, sizeof(DecisionTreeNode));

    forest->treeCount = numberOfTrees;
    forest->classCount = data->classCount;

    for (int i = 0; i < numberOfTrees; ++i) {
        Subproblem *sp = Dataset_bagging(data, baggingProportion);
        DecisionTreeNode *tree = DecisionTree_create(sp, 0, maxDepth, prunningThreshold);
        forest->trees[i] = tree;
        Subproblem_destroy(sp);
    }

    return forest;
}

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
Subproblem *Dataset_bagging(Dataset *data, float proportion) {

    int capacity = data->instanceCount * proportion;

    Subproblem *sp = Subproblem_create(capacity, data->featureCount, data->classCount);

    for (int i = 0; i < capacity; i++) {
        int randomIndex = rand() % data->instanceCount;
        Subproblem_insert(sp, &data->instances[randomIndex]);
    }

    return sp;
}

int RandomForest_predict(RandomForest *rf, Instance *instance) {
    int predictions[rf->treeCount][2]; // [0]: Prediction, [1] Number of votes for the prediction
    for (int i = 0; i < rf->treeCount; ++i) {
        predictions[i][0] = -1; // Invalid value to check if the cell is empty
    }

    for (int i = 0; i < rf->treeCount; ++i) {
        int prediction = DecisionTree_predict(rf->trees[i], instance);

        // Stock result in order to get the prediction with the most votes
        for (int j = 0; j < rf->treeCount; ++j) {
            if (predictions[j][0] == -1) {
                predictions[j][0] = prediction;
                predictions[j][1] = 1;
                break;
            }

            if (predictions[j][0] == prediction) {
                predictions[j][1] += 1;
                break; // Exit the loop once the prediction is found and updated
            }
        }
    }

    // Get the highest voted prediction
    int maxVoted = 0;
    int maxPrediction = 0;

    for (int i = 0; i < rf->treeCount; ++i) {
        if (predictions[i][0] == -1) {
            break;
        }
        if (predictions[i][1] > maxVoted) {
            maxVoted = predictions[i][1];
            maxPrediction = predictions[i][0];
        }
    }

    return maxPrediction;
}



float RandomForest_evaluate(RandomForest* rf, Dataset* data)
{
    int correctCount = 0;
    // Itère sur toutes les instances du dataset pour calculer le taux de réussite
    for (int i = 0; i < data->instanceCount; i++) {
        int prediction = RandomForest_predict(rf, &data->instances[i]);
        if (prediction == data->instances[i].classID)
            correctCount++;
    }
    return (float)correctCount / (float)data->instanceCount;
}

int RandomForest_nodeCount(RandomForest *rf) {

    int treeCount = 0;
    for (int i = 0; i < rf->treeCount; ++i) {
        treeCount += Decision_nodeCount(rf->trees[i]);
    }

    return treeCount;
}

void RandomForest_destroy(RandomForest *rf) {
    for (int i = 0; i < rf->treeCount; ++i) {
        free(rf->trees[i]);
    }

    free(rf);
}