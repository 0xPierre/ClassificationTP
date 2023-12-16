//
// Created by adrien on 12/16/23.
//

#include "../include/Split.h"
#include "math.h"

float Split_gini(Subproblem *sp, int featureID, float threshold) {

    Subproblem *subProblemLeft =
            Subproblem_create(
                    sp->instanceCount,
                    sp->instanceCount,
                    sp->classCount);
    Subproblem *subProblemRight =
            Subproblem_create(
                    sp->instanceCount,
                    sp->instanceCount,
                    sp->classCount);

    // Split instance to two sub problem, right and left
    for (int i = 0; i < sp->instanceCount; ++i) {
        if ((float) sp->instances[i]->values[featureID] < threshold) {
            Subproblem_insert(subProblemLeft, sp->instances[i]);
        } else {
            Subproblem_insert(subProblemRight, sp->instances[i]);
        }
    }

    float scoreLeft = Get_gini_score(subProblemLeft);
    float scoreRight = Get_gini_score(subProblemRight);

    float gini =
            ((float) subProblemLeft->instanceCount / (float) sp->instanceCount) * scoreLeft
            +
            ((float) subProblemRight->instanceCount / (float) sp->instanceCount) * scoreRight;


    Subproblem_destroy(subProblemLeft);
    Subproblem_destroy(subProblemRight);

    return gini;
}

float Get_gini_score(Subproblem *sp) {
    float score = .0f;

    for (int i = 0; i < sp->classCount; ++i) {
        score += (float) pow((float) sp->classes[i].instanceCount / (float) sp->instanceCount, 2);
    }

    return 1.0f - score;
}

Split Split_compute(Subproblem *subproblem) {
    float bestGini = INFINITY;
    Split split;

    for (int i = 0; i < subproblem->featureCount; ++i) {
        int min = (int) INFINITY;
        int max = 0;

        for (int j = 0; j < subproblem->instanceCount; ++j) {
            int feature = subproblem->instances[j]->values[i];
            if (feature > max) {
                max = feature;
            }
            if (feature < min) {
                min = feature;
            }
        }

        float threshold = ((float) min + (float) max) / 2;

        float gini = Split_gini(subproblem, i, threshold);

        if (gini < bestGini) {
            bestGini = gini;
            split.threshold = threshold;
            split.featureID = i;
        }
    }

    return split;
}