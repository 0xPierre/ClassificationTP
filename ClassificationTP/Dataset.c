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

	dataset->classCount = 0;
	dataset->featureCount = 0;
	dataset->instanceCount = 0;

	if (fscanf(file, "%d %d %d", &dataset->instanceCount, &dataset->classCount, &dataset->featureCount) != 3)
	{
		printf("Dataset file format error\n");
		free(dataset);
		return NULL;
	}

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


Subproblem* Subproblem_create(int maximumCapacity, int featureCount, int classCount) {
	Subproblem* subproblem = (Subproblem*)calloc(1, sizeof(Subproblem));
	if (subproblem == NULL) {
		printf("Subproblem Memory allocation failed - subproblem\n");
		return NULL;
	}

	subproblem->featureCount = featureCount;
	subproblem->classCount = classCount;
	subproblem->instanceCount = 0;
	subproblem->capacity = maximumCapacity;

	// Alloue le tableau de pointeurs d'instances à la capacité max
	subproblem->instances = (Instance**)calloc(maximumCapacity, sizeof(Instance*));

	if (subproblem->instances == NULL) {
		printf("Subproblem Memory allocation failed - instances\n");
		return NULL;
	}

	// Alloue le tableau de pointeurs de sous class
	subproblem->classes = (SubproblemClass*)calloc(classCount, sizeof(SubproblemClass));

	if (subproblem->classes == NULL) {
		printf("Subproblem Memory allocation failed - classes\n");
		return NULL;
	}

	// Alloue les instances pour chaque classes
	for (int i = 0; i < classCount; i++)
	{
		subproblem->classes[i].instances = (Instance**)calloc(maximumCapacity, sizeof(Instance*));
		if (subproblem->classes[i].instances == NULL) {
			printf("Subproblem Memory allocation failed - instances class\n");
			return NULL;
		}
	}

	return subproblem;
}


void Subproblem_insert(Subproblem* subproblem, Instance* instance)
{
	// Insère l'adresse de l'instance dans le tableau principal
	subproblem->instances[subproblem->instanceCount] = instance;

	// Insère l'adresse de l'instance dans le tableau dédié à sa classe
	int classId = instance->classID;

	subproblem->classes[classId].instances[
		subproblem->classes[classId].instanceCount
	] = instance;
	subproblem->classes[classId].instanceCount++;

	// Incrémente le nombre d'instances
	subproblem->instanceCount++;
}


void Subproblem_destroy(Subproblem* subproblem) {
	for (int i = 0; i < subproblem->classCount; i++) {
		free(subproblem->classes[i].instances);
	}
	
	free(subproblem->classes);
	free(subproblem->instances);
	free(subproblem);
}


void Dataset_destroy(Dataset* dataset) {
	for (int i = 0; i < dataset->instanceCount; i++) {
		free(dataset->instances[i].values);
	}
	free(dataset->instances);
	free(dataset);
}


Subproblem* Dataset_getSubproblem(Dataset* data) {
	if (data == NULL) {
		printf("Dataset is NULL\n");
		return NULL;
	}

	// Création du sous problème
	Subproblem* subproblem = Subproblem_create(
		data->instanceCount, data->featureCount, data->classCount
	);

	// Ajout des instances dans le sous problème
	for (int i = 0; i < data->instanceCount; i++) {
		Subproblem_insert(subproblem, &data->instances[i]);
	}

	return subproblem;
}


void Subproblem_print(Subproblem* subproblem) {
	printf("Dataset with %d classes of %d features\n", subproblem->classCount, subproblem->featureCount);
	printf("Size = %d, capacity = %d\n", subproblem->instanceCount, subproblem->capacity);

	for (int i = 0; i < subproblem->classCount; i++) {
		printf("- class %d: %d instances\n", i, subproblem->classes[i].instanceCount);
	}
}