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