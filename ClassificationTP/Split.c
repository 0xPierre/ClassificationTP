#include "Settings.h"


float Split_gini(Subproblem *sp, int featureID, float threshold) {
    int instanceCount = sp->instanceCount;

    Subproblem *leftSubproblem = Subproblem_create(instanceCount, sp->featureCount, sp->classCount);
    Subproblem *rightSubproblem = Subproblem_create(instanceCount, sp->featureCount, sp->classCount);

    if (leftSubproblem == NULL || rightSubproblem == NULL) {
        printf("Subproblem Memory allocation failed - left or right Subproblem\n");
        return -1.0f;
    }

    // Division des instances en fonction du seuil
    for (int i = 0; i < instanceCount; i++) {
        Instance *instance = sp->instances[i];

        if (instance->values[featureID] <= threshold) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
            if (strcmp(POWER_MODE(), "efficient") == 0 && (instance->values[featureID] == threshold)) {
                Subproblem_insert(rightSubproblem, instance);
            } else {
                Subproblem_insert(leftSubproblem, instance);
            }
#pragma clang diagnostic pop
        } else {
            Subproblem_insert(rightSubproblem, instance);
        }
    }

    // Récupération du Gini pour chaque sous problème
    float giniLeft = calculate_gini(leftSubproblem);
    float giniRight = calculate_gini(rightSubproblem);

    // On pondère le gini en fonction du total
    float gini =
            ((float) leftSubproblem->instanceCount / instanceCount) * giniLeft
            +
            ((float) rightSubproblem->instanceCount / instanceCount) * giniRight;

    Subproblem_destroy(leftSubproblem);
    Subproblem_destroy(rightSubproblem);

    return gini;
}

float calculate_gini(Subproblem *subproblem) {
    float gini = 1.0f;
    // Calcule le gini
    for (int i = 0; i < subproblem->classCount; i++) {
        float p = (float) subproblem->classes[i].instanceCount / (float) subproblem->instanceCount;
        gini -= p * p;
    }

    return gini;
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

        if (strcmp(POWER_MODE(), "efficient") == 0) {
            for (int y = min; y <= max; ++y) {
                // Calcul le meilleur gini
                float gini = Split_gini(subproblem, i, (float) y);

                if (gini < bestGini) {
                    bestGini = gini;
                    split.featureID = i;
                    split.threshold = (float) y;
                }
            }
        } else {
            float threshold = ((float) min + (float) max) / 2;

            float gini = Split_gini(subproblem, i, threshold);

            if (gini < bestGini) {
                bestGini = gini;
                split.threshold = threshold;
                split.featureID = i;
            }
        }
    }

    return split;
}