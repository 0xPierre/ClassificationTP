#include "Settings.h"

Dataset* Dataset_readFromFile(char* filename) {
	FILE* file = fopen(filename, "r");

	if (file == NULL) {
		printf("File not found: %s\n", filename);
		return NULL;
	}

	Dataset* dataset = (Dataset*)malloc(sizeof(Dataset));

	if (dataset == NULL) {
		printf("Dataset Memory allocation failed\n");
		return NULL;
	}

	int _ = fscanf(file, "%d %d %d", &dataset->instanceCount, &dataset->classCount, &dataset->featureCount);

	dataset->instances = (Instance*)malloc(dataset->instanceCount * sizeof(Instance));

	for (int i = 0; i < dataset->instanceCount; i++) {
		int _ = fscanf(file, "%d", &dataset->instances[i].classID);

		dataset->instances[i].values = (int*)malloc(dataset->featureCount * sizeof(int));

		for (int j = 0; j < dataset->featureCount; j++) {
			int _ = fscanf(file, "%d", &dataset->instances[i].values[j]);
		}
	}

	return dataset;
}

void Dataset_destroy(Dataset* dataset) {
	for (int i = 0; i < dataset->instanceCount; i++) {
		free(dataset->instances[i].values);
	}
	free(dataset->instances);
	free(dataset);
}

Subproblem* Dataset_getSubproblem(Dataset* data) {
	Subproblem *subproblem = (Subproblem*)calloc(1, sizeof(Subproblem));

	if (subproblem == NULL) {
		printf("Subproblem Memory allocation failed\n");
		return NULL;
	}

	subproblem->instanceCount = data->instanceCount;
	subproblem->featureCount = data->featureCount;
	subproblem->classCount = data->classCount;
	subproblem->capacity = data->instanceCount;
	
	subproblem->instances = (Instance **)calloc(subproblem->instanceCount, sizeof(Instance*));

	for (int i = 0; i < subproblem->instanceCount; i++) {
		subproblem->instances[i] = &data->instances[i];
	}

	subproblem->classes = (SubproblemClass*)calloc(subproblem->classCount, sizeof(SubproblemClass));

	// not finished

	return subproblem;
}


Subproblem* Subproblem_create(int maximumCapacity, int featureCount, int classCount) {
	Subproblem* subproblem = (Subproblem*)calloc(1, sizeof(Subproblem));
	if (subproblem == NULL) {
		printf("Subproblem Memory allocation failed\n");
		return NULL;
	}

	subproblem->featureCount = featureCount;
	subproblem->classCount = classCount;

	// not finished

	return subproblem;
}

void Subproblem_destroy(Subproblem* subproblem) {
	for (int i = 0; i < subproblem->instanceCount; i++) {
		free(subproblem->instances[i]);
	}
	free(subproblem->instances);
	free(subproblem);

	// not finished
}

void Subproblem_print(Subproblem* subproblem) {
	printf("Dataset with %d classes of %d features\n", subproblem->classCount, subproblem->featureCount);
	printf("Size = %d, capacity = %d\n", subproblem->instanceCount, subproblem->capacity);

	for (int i = 0; i < subproblem->classCount; i++) {
		printf("- class %d: %d instances\n", i, subproblem->classes[0].instanceCount);
	}
}