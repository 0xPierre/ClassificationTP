//
// Created by adrien on 12/11/23.
//

#include "Dataset.h"

#include <stdio.h>
#include <stdlib.h>

Dataset *Dataset_readFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("An error occurred while reading the file...\n");
        return NULL;
    };

    Dataset *dataset = calloc(1, sizeof(Dataset));

    fscanf(file, "%d", &dataset->instanceCount);
    fscanf(file, "%d", &dataset->classCount);
    fscanf(file, "%d", &dataset->featureCount);


    dataset->instances = calloc(dataset->instanceCount, sizeof(Instance));
    for (int i = 0; i < dataset->instanceCount; i++) {
        dataset->instances[i].values = (int *) calloc(dataset->featureCount, sizeof(int));
        for (int y = 0; y < dataset->featureCount; y++) {
            fscanf(file, "%d", &dataset->instances[i].values[y]);
        }
    }

    fclose(file);
    return dataset;
}

void Dataset_destroy(Dataset *data) {
    if (data == NULL) {
        return;
    }
    for (int i = 0; i < data->instanceCount; i++) {
        free(data->instances[i].values);
    }
    free(data->instances);
    free(data);
}

Subproblem *Dataset_getSubproblem(Dataset *data) {
    if (data == NULL) {
        printf("ERROR: Data can't be null...\n");
        return NULL;
    }
    Subproblem *subproblem = (Subproblem *) malloc(sizeof(Subproblem));

    subproblem->instanceCount = data->instanceCount;
    subproblem->featureCount = data->featureCount;
    subproblem->classCount = data->classCount;

    subproblem->instances = (Instance **) malloc(data->instanceCount * sizeof(Instance *));

    for (int i = 0; i < data->instanceCount; i++) {
        subproblem->instances[i] = &data->instances[i];
    }

    subproblem->capacity = data->instanceCount; // Set capacity to the initial instance count
    subproblem->featureCount = data->featureCount;
    subproblem->classCount = data->classCount;

    subproblem->classes = (SubproblemClass *) malloc(data->classCount * sizeof(SubproblemClass));

    for (int i = 0; i < data->classCount; i++) {
        subproblem->classes[i].instanceCount = 0;
        subproblem->classes[i].instances = NULL;
    }

    return subproblem;
}

Subproblem *Subproblem_create(int maximumCapacity, int featureCount, int classCount) {
    Subproblem *subproblem = (Subproblem *)malloc(sizeof(Subproblem));

    subproblem->instances = (Instance **)malloc(maximumCapacity * sizeof(Instance *));
    subproblem->instanceCount = 0;
    subproblem->capacity = maximumCapacity;
    subproblem->featureCount = featureCount;
    subproblem->classCount = classCount;

    subproblem->classes = (SubproblemClass *)malloc(classCount * sizeof(SubproblemClass));

    for (int i = 0; i < classCount; i++) {
        subproblem->classes[i].instanceCount = 0;
        subproblem->classes[i].instances = NULL;
    }

    return subproblem;
}

void Subproblem_destroy(Subproblem *subproblem) {
    if (subproblem == NULL) {
        return;
    }

    free(subproblem->instances);

    // Deallocate memory for instances in each class array
    for (int i = 0; i < subproblem->classCount; i++) {
        SubproblemClass *classArray = &(subproblem->classes[i]);
        free(classArray->instances);
    }

    // Deallocate memory for the array of SubproblemClass structures
    free(subproblem->classes);

    free(subproblem);
}

void Subproblem_insert(Subproblem *subproblem, Instance *instance) {
    if (subproblem->instanceCount < subproblem->capacity) {
        subproblem->instances[subproblem->instanceCount] = instance;

        subproblem->instanceCount++;

        // Find the class ID of the instance
        int classID = instance->classID;

        // Check if the class ID is valid
        if (classID >= 0 && classID < subproblem->classCount) {
            // Insert the instance into the array dedicated to its class
            SubproblemClass *classArray = &(subproblem->classes[classID]);
            classArray->instances = realloc(classArray->instances, (classArray->instanceCount + 1) * sizeof(Instance *));
            classArray->instances[classArray->instanceCount] = instance;
            classArray->instanceCount++;
        } else {
            printf("Error: Invalid class ID %d for instance.\n", classID);
        }
    } else {
        printf("Error: Subproblem capacity exceeded. Unable to insert instance.\n");
    }
}

void Subproblem_print(Subproblem *subproblem) {
    if (subproblem == NULL) {
        return;
    }

    printf("Dataset with %d classes of %d features\n", subproblem->classCount, subproblem->featureCount);
    printf("Size = %d, capacity = %d\n", subproblem->instanceCount, subproblem->capacity);

    for (int i = 0; i < subproblem->classCount; i++) {
        printf("- class %d: %d instances\n", i, subproblem->classes[i].instanceCount);
    }
}
