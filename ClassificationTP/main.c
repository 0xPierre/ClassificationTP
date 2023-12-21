#include "Settings.h"


DecisionArgs Args = {
    .split = GINI_NORMAL,
    .featureBaggingProportion = 1.f,
    .useFeatureBagging = false,
    .useLocalFeatureBagging = false,
    .instanceBaggingProportion = 1.f,
    .useInstanceBagging = false,
    .isSilent = false,
    .prunningThreshold = 1.f,
    .treeCount = 1,
    .maxDepth = 30,
    .pathForest = "",
    .trainPath = NULL,
    .testPath = NULL,
    .filters = "\0",
    .filtersDatasets = false,
    .pathSaveForest = NULL,
    .saveForest = false,
};

int main(int argc, char* args[]) {

    time_t start = time(NULL);

    strcpy(Args.trainPath, "../Datasets/MNIST_train.txt");
    strcpy(Args.testPath, "../Datasets/MNIST_test.txt");

    //strcpy(Args.pathForest, "../Forests/MNIST_FILTERED_HYPERPARAMETERS_98_65.bfm");
    Args.filtersDatasets = true;
    Args.filters[0] = '0';
    Args.filters[1] = '1';
    // Add a second 1 filter improve by 0.03%
    //Args.filters[2] = '1';

    Args.saveForest = true;
    strcpy(Args.pathSaveForest, "../Forests/newForestTest.dfm");

    Args.treeCount = 20;
    Args.useLocalFeatureBagging = true;


    StartTest();

    time_t end = time(NULL);
    printf("Execution time: %d seconds\n", (int)(end - start));

    return 0;
}