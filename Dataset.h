#ifndef DATASET_H
#define DATASET_H

typedef struct sInstance{
    int* values;
    int classID;
} Instance;

typedef struct sDataset{
    Instance *instances;
    int instanceCount;
    int featureCount;
    int classCount;
} Dataset;

typedef struct sSubproblemClass{
    int instanceCount;
    Instance **instances;
} SubproblemClass;

typedef struct sSubproblem{
    Instance **instances;
    int instanceCount;
    int capacity;
    int featureCount;
    int classCount;
    SubproblemClass *classes;
} Subproblem;
#endif // DATASET_H


/**
 * @brief Reads a dataset from a file and returns a pointer to the created Dataset structure.
 *
 * The file should have the following format:
 *   - The first line: Number of instances in the dataset
 *   - The second line: Number of classes in the dataset
 *   - The third line: Number of features for each instance
 *   - The following lines: Instance values separated by spaces, one instance per line
 *
 * @param filename The name of the file to read the dataset from.
 * @return A pointer to the created Dataset structure, or NULL if an error occurs.
 */
Dataset* Dataset_readFromFile(char* filename);