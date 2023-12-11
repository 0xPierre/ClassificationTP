#pragma once

typedef struct sInstance {
	int* values;
	int classID;
} Instance;
	Instance* instances;
	int instanceCount;
	int featureCount;
	int classCount;
} Dataset;
	int instanceCount;
	Instance** instances;
} SubproblemClass;

typedef struct sSubproblem {
	Instance** instances;
	int instanceCount;
	int capacity;
	int featureCount;
	int classCount;
	SubproblemClass* classes;
} Subproblem;