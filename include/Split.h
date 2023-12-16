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