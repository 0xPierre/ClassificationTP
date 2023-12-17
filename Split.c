#include "Settings.h"



float calculate_gini(Subproblem* subproblem) {
    float gini = 1.0f;
	// Calcule le gini
    for (int i = 0; i < subproblem->classCount; i++) {
		float p = (float)subproblem->classes[i].instanceCount / (float)subproblem->instanceCount;
		gini -= p * p;
	}

	return gini;
}

float Split_gini(Subproblem* sp, int featureID, float threshold) {
	int instanceCount = sp->instanceCount;

	// Création des subproblemes droite gauche
	Subproblem* leftSubproblem = Subproblem_create(instanceCount, sp->featureCount, sp->classCount);
	Subproblem* rightSubproblem = Subproblem_create(instanceCount, sp->featureCount, sp->classCount);

	if (leftSubproblem == NULL || rightSubproblem == NULL) {
		printf("Subproblem Memory allocation failed - left or right Subproblem\n");
		return -1.0f;
	}

	// Division des instances en fonction du seuil
	for (int i = 0; i < instanceCount; i++) {
		Instance* instance = sp->instances[i];

		if (instance->values[featureID] <= threshold) {
			Subproblem_insert(leftSubproblem, instance);
		}
		else {
			Subproblem_insert(rightSubproblem, instance);
		}
	}

	// Récupération du Gini pour chaque sous problème
	float giniLeft = calculate_gini(leftSubproblem);
	float giniRight = calculate_gini(rightSubproblem);

	// On pondère le gini en fonction du total
	float gini =
		((float)leftSubproblem->instanceCount / instanceCount) * giniLeft
		+
		((float)rightSubproblem->instanceCount / instanceCount) * giniRight;

	Subproblem_destroy(leftSubproblem);
	Subproblem_destroy(rightSubproblem);

	return gini;
}


Split Split_compute(Subproblem* subproblem) {
	// Valeur max
	float bestGini = FLT_MAX;
	Split bestSplit;
	
	// On itère sur toutes les features
	for (int featureId = 0; featureId < subproblem->featureCount; featureId++) {
		// On cherche minj et maxj
		int minj = subproblem->instances[0]->values[featureId];
		int maxj = subproblem->instances[0]->values[featureId];

		// Comme minj et maxj ont déjà la valeur de la première instance, i=1
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

		if (gini <= bestGini) {
			bestGini = gini;
			bestSplit.featureID = featureId;
			bestSplit.threshold = threshold;
		}
	}
	return bestSplit;
}