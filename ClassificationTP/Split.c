#include "Settings.h"



float calculate_gini(Subproblem* subproblem) {
    float instanceCount = (float)subproblem->instanceCount > 0 ? (float)subproblem->instanceCount : 1.0f;
    float gini = 1.0f;
    // Calcule le gini
    for (int i = 0; i < subproblem->classCount; i++) {
        float p = (float)subproblem->classes[i].instanceCount / instanceCount;
        gini -= p * p;
    }

    return gini;
}

float Split_gini(Subproblem* sp, int featureID, float threshold) {
    int instanceCount = sp->instanceCount;

    // Cr�ation des subproblemes droite gauche
    Subproblem* leftSubproblem = Subproblem_create(instanceCount, sp->featureCount, sp->classCount);
    Subproblem* rightSubproblem = Subproblem_create(instanceCount, sp->featureCount, sp->classCount);

    if (leftSubproblem == NULL || rightSubproblem == NULL) {
        printf("Subproblem Memory allocation failed - left or right Subproblem\n");
        return -1.0f;
    }

    // Division des instances en fonction du seuil
    for (int i = 0; i < instanceCount; i++) {
        Instance* instance = sp->instances[i];
        if (instance->values[featureID] < threshold) {
            Subproblem_insert(leftSubproblem, instance);
        }
        else {
            Subproblem_insert(rightSubproblem, instance);
        }
    }

    // R�cup�ration du Gini pour chaque sous probl�me
    float giniLeft = calculate_gini(leftSubproblem);
    float giniRight = calculate_gini(rightSubproblem);

   /* if (giniLeft == 0) giniLeft = 0.0001f;
    if (giniRight -) giniRight = 0.0001f;*/

    float gini =
        ((float)leftSubproblem->instanceCount / instanceCount) * giniLeft
        +
        ((float)rightSubproblem->instanceCount / instanceCount) * giniRight;

    Subproblem_destroy(leftSubproblem);
    Subproblem_destroy(rightSubproblem);

    return gini;
}


Split Split_compute_normal(Subproblem* subproblem, bool* authorizedFeatures) {
    // Valeur max
    float bestGini = FLT_MAX;
    Split bestSplit;

    bool *localAuthorizedFeatures = (bool *)calloc(subproblem->featureCount, sizeof(bool));
    if (Args.useLocalFeatureBagging) {
        AssertNew(localAuthorizedFeatures);

        int localAuthorizedFeaturesCount = sqrt(subproblem->featureCount);
        //int localAuthorizedFeaturesCount = (int)((float)subproblem->featureCount * (sqrtf(Args.featureBaggingProportion) / (float)subproblem->featureCount));
        for (int i = 0; i < localAuthorizedFeaturesCount; i++) {
            int randomIndex = ((rand() ^ (rand() << 15)) & 0x7FFFFFFF) % subproblem->featureCount;
            localAuthorizedFeatures[randomIndex] = true;
        }
    }

    // On itere sur toutes les features
    for (int featureId = 0; featureId < subproblem->featureCount; featureId++) {
        // Lorsque l'on utilise le bagging, on ne prend pas en compte les features non autorises
        if (Args.useFeatureBagging && !authorizedFeatures[featureId]) continue;
        if (Args.useLocalFeatureBagging && !localAuthorizedFeatures[featureId]) continue;
        // On cherche minj et maxj
        int minj = subproblem->instances[0]->values[featureId];
        int maxj = subproblem->instances[0]->values[featureId];

        // Comme minj et maxj ont deja la valeur de la premiere instance, i=1
        for (int i = 1; i < subproblem->instanceCount; i++) {
            int tmpFeature = subproblem->instances[i]->values[featureId];
            if (tmpFeature > maxj)
                maxj = tmpFeature;

            if (tmpFeature <= minj) {
                minj = tmpFeature;
            }
        }

        float threshold = ((float)maxj + (float)minj) / 2;

        // Calcul le meilleur gini
        float gini = Split_gini(subproblem, featureId, threshold);
        if (gini < bestGini) {
            bestGini = gini;
            bestSplit.featureID = featureId;
            bestSplit.threshold = threshold;
        }
    }
    return bestSplit;
}

Split Split_compute_less_node(Subproblem* subproblem, bool* authorizedFeatures) {
    // Valeur max
    float bestGini = FLT_MAX;
    Split bestSplit;

    // On itere sur toutes les features
    for (int featureId = 0; featureId < subproblem->featureCount; featureId++) {
        // Lorsque l'on utilise le bagging, on ne prend pas en compte les features non autorises
        if (Args.useFeatureBagging && !authorizedFeatures[featureId]) continue;
        // On cherche minj et maxj
        int minj = subproblem->instances[0]->values[featureId];
        int maxj = subproblem->instances[0]->values[featureId];

        // Comme minj et maxj ont deja la valeur de la premiere instance, i=1
        for (int i = 1; i < subproblem->instanceCount; i++) {
            int tmpFeature = subproblem->instances[i]->values[featureId];
            if (tmpFeature > maxj)
                maxj = tmpFeature;

            if (tmpFeature <= minj) {
                minj = tmpFeature;
            }
        }

        // On cherche le meilleur seuil entre minj et maxj
        for (int j = minj; j < maxj; j++) {
            float threshold = (float)j;
			// Calcul le meilleur gini
			float gini = Split_gini(subproblem, featureId, threshold);
            if (gini < bestGini) {
				bestGini = gini;
				bestSplit.featureID = featureId;
				bestSplit.threshold = threshold;
			}
        }
    }
    return bestSplit;
}

Split Split_compute(Subproblem* subproblem, bool *authorizedFeatures) {
    if (Args.split == GINI_NORMAL) {
        return Split_compute_normal(subproblem, authorizedFeatures);
    }
    else if (Args.split == GINI_LESS_NODE) {
        Split_compute_less_node(subproblem, authorizedFeatures);
    }
    else {
        printf("Split type not recognized\n");
        assert(false);
    }
}