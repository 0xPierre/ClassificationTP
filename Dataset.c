//
// Created by adrien on 12/11/23.
//

#include "Dataset.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dataset *Dataset_readFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("An error occurred while reading the file...\n");
        return NULL;
    }

    Dataset *dataset = calloc(1, sizeof(Dataset));

    fscanf(file,
           "%d %d %d",
           &dataset->instanceCount,
           &dataset->classCount,
           &dataset->featureCount);

    dataset->instances = calloc(dataset->instanceCount, sizeof(Instance));

    for (int i = 0; i < dataset->instanceCount; i++) {
        dataset->instances[i].values = (int *) calloc(dataset->featureCount, sizeof(int));
        fscanf(file, "%d", &dataset->instances[i].classID); // Get class ID
        for (int y = 0; y < dataset->featureCount; y++) {
            fscanf(file, "%d", &dataset->instances[i].values[y]); // Get features
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
    if (subproblem == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed for Subproblem...\n");
        return NULL;
    }

    subproblem->instanceCount = data->instanceCount;
    subproblem->featureCount = data->featureCount;
    subproblem->classCount = data->classCount;
    subproblem->capacity = data->instanceCount; // Set capacity to the initial instance count

    subproblem->instances = (Instance **) malloc(data->instanceCount * sizeof(Instance *));

    // Some tmp vars for counting instant for each class and store instances
    int classCount[data->classCount];
    memset(classCount, 0, data->classCount * sizeof(int));

    int classIDMemory, classCountIndex = -1;

    for (int i = 0; i < data->instanceCount; i++) {
        subproblem->instances[i] = &data->instances[i];

        // The lines below are computed the number of instant for each class
        if (classIDMemory != data->instances[i].classID) {
            classCountIndex ++;
        }
        classCount[classCountIndex] ++;
        classIDMemory = data->instances[i].classID;
    }

    subproblem->classes = (SubproblemClass *) calloc(data->classCount, sizeof(SubproblemClass));
    if (subproblem->classes == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed for Subproblem classes...\n");
        Subproblem_destroy(subproblem);
        return NULL;
    }

    for (int i = 0; i < data->classCount; i++) {
        subproblem->classes[i].instanceCount = classCount[i];
        subproblem->classes[i].instances = NULL;
    }

    for (int i = 0; i < data->classCount; i++) {
        subproblem->classes[i].instanceCount = classCount[i];
        subproblem->classes[i].instances = (Instance **)malloc(classCount[i] * sizeof(Instance *));
        if (subproblem->classes[i].instances == NULL) {
            fprintf(stderr, "ERROR: Memory allocation failed for Subproblem class instances...\n");
            Subproblem_destroy(subproblem);
            return NULL;
        }

        // Fill in instances for each class
        int instanceIndex = 0;
        for (int j = 0; j < data->instanceCount; j++) {
            if (data->instances[j].classID == i) {
                subproblem->classes[i].instances[instanceIndex++] = &data->instances[j];
            }
        }
    }

    return subproblem;
}

Subproblem *Subproblem_create(int maximumCapacity, int featureCount, int classCount) {
    Subproblem *subproblem = (Subproblem *) malloc(sizeof(Subproblem));

    subproblem->instances = (Instance **) malloc(maximumCapacity * sizeof(Instance *));
    subproblem->instanceCount = 0;
    subproblem->capacity = maximumCapacity;
    subproblem->featureCount = featureCount;
    subproblem->classCount = classCount;

    subproblem->classes = (SubproblemClass *) malloc(classCount * sizeof(SubproblemClass));

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
        free(subproblem->classes[i].instances);
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
            classArray->instances = realloc(classArray->instances,
                                            (classArray->instanceCount + 1) * sizeof(Instance *));
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
