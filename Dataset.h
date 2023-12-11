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


/**
 * @brief Destroys a Dataset object and frees up all memory.
 *
 * This function will destroy the given Dataset object and free up all the memory
 * allocated for it. It ensures that all instances and their values are also freed
 * before releasing the memory occupied by the Dataset object itself.
 *
 * @param data The Dataset object to be destroyed.
 */
void Dataset_destroy(Dataset *data);

/**
 * @brief Retrieves a subproblem from a dataset.
 *
 * This function creates a subproblem based on the specified dataset. The subproblem is a subset of the original dataset, containing the references to the instances from the dataset
*.
 *
 * @param[in] data The dataset from which to create the subproblem.
 * @return A pointer to the created subproblem.
 *         - If the data is NULL, an error message is printed and NULL is returned.
 *         - If the memory allocation fails, NULL is returned.
 *
 * @see Dataset
 * @see Subproblem
 * @see Instance
 * @see SubproblemClass
 */
Subproblem *Dataset_getSubproblem(Dataset *data);

/**
 * @brief Create a new Subproblem.
 *
 * This function creates a new Subproblem with the given parameters.
 *
 * @param maximumCapacity The maximum capacity of the Subproblem's instance array.
 * @param featureCount The number of features in the Subproblem.
 * @param classCount The number of classes in the Subproblem.
 *
 * @return A pointer to the newly created Subproblem.
 */
Subproblem *Subproblem_create(int maximumCapacity, int featureCount, int classCount);

/**
 * @brief Destroys a Subproblem object and frees the associated memory.
 *
 * @param subproblem The Subproblem object to destroy.
 */
void Subproblem_destroy(Subproblem *subproblem);


/**
 * @brief Inserts the address of an instance into the Subproblem.
 *
 * Inserts the instance address both in the main array and the array dedicated to the
 * instance's class. Updates the count of considered instances in the Subproblem.
 *
 * @param subproblem A pointer to the Subproblem structure.
 * @param instance A pointer to the Instance structure to be inserted.
 */
void Subproblem_insert(Subproblem *subproblem, Instance *instance);


/**
 * @brief Prints information about a Subproblem.
 * @param subproblem The Subproblem to be printed.
 * @return void
 *
 * This function prints the following information about the given Subproblem:
 * - The number of classes and features in the dataset.
 * - The size and capacity of the Subproblem.
 * - The number of instances for each class.
 **/
void Subproblem_print(Subproblem *subproblem);