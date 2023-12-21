#include "Settings.h"

Dataset* DatasetCountWhite(Dataset* dataset) {
	Dataset* newDataset = (Dataset*)calloc(1, sizeof(Dataset));
	AssertNew(newDataset);

	newDataset->instances = (Instance*)calloc(dataset->instanceCount, sizeof(Instance));
	newDataset->instanceCount = dataset->instanceCount;
	AssertNew(newDataset->instances);

	newDataset->featureCount = dataset->featureCount + 1;
	newDataset->classCount = dataset->classCount;

	for (int i = 0; i < newDataset->instanceCount; i++) {
		int whiteCount = 0;

		newDataset->instances[i].values = (int*)calloc(newDataset->featureCount, sizeof(int));
		AssertNew(newDataset->instances[i].values);

		newDataset->instances[i].classID = dataset->instances[i].classID;


		for (int j = 0; j < newDataset->featureCount - 1; j++) {
			newDataset->instances[i].values[j] = dataset->instances[i].values[j];

			if (newDataset->instances[i].values[j] >= 230) {
				whiteCount++;
			}
		}
		newDataset->instances[i].values[newDataset->featureCount - 1] = whiteCount;
	}

	return newDataset;
}

Dataset* ConcatenateTwoDatasetFeatures(Dataset* dataset1, Dataset* dataset2) {
	Dataset* newDataset = (Dataset*)calloc(1, sizeof(Dataset));
	AssertNew(newDataset);
	newDataset->instances = (Instance*)calloc(dataset1->instanceCount, sizeof(Instance));

	newDataset->instanceCount = dataset1->instanceCount;
	AssertNew(newDataset->instances);

	newDataset->featureCount = dataset1->featureCount + dataset2->featureCount;
	newDataset->classCount = dataset1->classCount;
	printf("%d %d %d\n", newDataset->instanceCount, newDataset->featureCount, newDataset->classCount);
	
	for (int i = 0; i < newDataset->instanceCount; i++) {
		newDataset->instances[i].values = (int*)calloc(newDataset->featureCount, sizeof(int));
		AssertNew(newDataset->instances[i].values);

		newDataset->instances[i].classID = dataset1->instances[i].classID;

		for (int j = 0; j < dataset1->featureCount; j++) {
			newDataset->instances[i].values[j] = dataset1->instances[i].values[j];
		}

		for (int j = 0; j < dataset2->featureCount; j++) {
			newDataset->instances[i].values[dataset1->featureCount + j] = dataset2->instances[i].values[j];
		}
	}

	return newDataset;
}


void TransFormGrayToWhiteOneFeature(int* values, int featureCount, int threshold, bool setToMin, int min, int max) {
	for (int i = 0; i < featureCount; i++) {
		if (values[i] >= threshold) {
			values[i] = max;
		}
		else if (setToMin) {
			values[i] = min;
		}
	}
}

void TransformGrayToWhite(Dataset* dataset, int threshold, bool setToMin, int min, int max) {
	for (int i = 0; i < dataset->instanceCount; i++) {
		TransFormGrayToWhiteOneFeature(dataset->instances[i].values, dataset->featureCount, threshold, setToMin, min, max);
	}
}



int calculate_median(int* matrix, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (matrix[j] > matrix[j + 1]) {
                int temp = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = temp;
            }
        }
    }

    if (size % 2 == 0) {
        return (matrix[size / 2 - 1] + matrix[size / 2]) / 2;
    }
    else {
		return matrix[size / 2];
    }
}

void ApplyMedianFilter(Dataset* dataset) {
    for (int i = 0; i < dataset->instanceCount; ++i) {
        for (int j = 0; j < dataset->featureCount; ++j) {
            // pixelValues = matrix of 9 pixels, representing the 3x3 matrix
            int* pixelValues = (int *)calloc(9,sizeof(int));
            int index = 0;
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int rIndex = i + x;
                    int cIndex = j + y;
                    if (rIndex >= 0 && rIndex < dataset->instanceCount &&
                        cIndex >= 0 && cIndex < dataset->featureCount) {
                        pixelValues[index++] = dataset->instances[rIndex].values[cIndex];
                    }
                }
            }

            dataset->instances[i].values[j] = calculate_median(pixelValues, index);
            free(pixelValues);
        }
    }
}


Dataset* CopyDataset(Dataset* dataset) {
	Dataset* newDataset = (Dataset*)calloc(1, sizeof(Dataset));
	AssertNew(newDataset);

	newDataset->instances = (Instance*)calloc(dataset->instanceCount, sizeof(Instance));
	newDataset->instanceCount = dataset->instanceCount;
	AssertNew(newDataset->instances);

	newDataset->featureCount = dataset->featureCount;
	newDataset->classCount = dataset->classCount;

	for (int i = 0; i < newDataset->instanceCount; i++) {
		newDataset->instances[i].values = (int*)calloc(newDataset->featureCount, sizeof(int));
		AssertNew(newDataset->instances[i].values);

		newDataset->instances[i].classID = dataset->instances[i].classID;
		for (int j = 0; j < newDataset->featureCount; j++) {
			newDataset->instances[i].values[j] = dataset->instances[i].values[j];
		}
	}
	return newDataset;
}


