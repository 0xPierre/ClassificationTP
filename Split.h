#include "Settings.h"

typedef struct sSplit {
	int featureID;
	float threshold;
} Split;

float Split_gini(Subproblem* sp, int featureID, float threshold);

Split Split_compute(Subproblem* subproblem);