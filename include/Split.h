//
// Created by adrien on 12/16/23.
//

#include "Dataset.h"

#ifndef CLASSIFICATIONTP_SPLIT_H
#define CLASSIFICATIONTP_SPLIT_H

typedef struct sSplit{
    int featureID;
    float threshold;
} Split;

#endif //CLASSIFICATIONTP_SPLIT_H

/**
 * Calculates the Gini impurity score after splitting a subproblem based on a specified feature and threshold.
 *
 * @param sp            The subproblem to be split.
 * @param featureID     The ID of the feature used for splitting.
 * @param threshold     The threshold value for the feature to determine the split.
 * @return              The Gini impurity score after the split.
 */
float Split_gini(Subproblem *sp, int featureID, float threshold);

/**
 * Calculates the Gini impurity score for a given subproblem.
 *
 * @param sp    The subproblem for which to calculate the Gini impurity.
 * @return      The Gini impurity score.
 */
float Get_gini_score(Subproblem * sp);

/**
 * @brief Computes the best split for a given subproblem using Gini impurity.
 *
 * This function iterates through each feature in the subproblem and finds the best
 * split based on Gini impurity. The best split is determined by minimizing the Gini
 * impurity across all features and their corresponding thresholds.
 *
 * @param subproblem The subproblem for which the split is computed.
 * @return The best split found, including the feature ID and threshold.
 */
Split Split_compute(Subproblem *subproblem);