#include "Settings.h"

// Merci de descendre juste en dessous pour avoir accès aux différents configurations possibles.

DecisionArgs Args = {
    .split = GINI_NORMAL,
    .featureBaggingProportion = 1.f,
    .useFeatureBagging = false,
    .useLocalFeatureBagging = false,
    .instanceBaggingProportion = 1.f, // Ne pas modifier
    .useInstanceBagging = false, // Ne pas modifier
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

// Bonjour, voici les différents configuration possibles permettant de tester notre travail.
// Pour tester une configuration, il suffit de mettre la valeur à true et de lancer le programme.
// Attention, merci d'au moins mettre le premier define de chaque paquet à false si ce n'est pas celui sélectionner.

// Permet de tester la création d'un arbre de décision simple, sans forêt, avec le calcul du gini (minj+maxj)/2.
#define TEST_SIMPLE_PENDIGITS false


// Permet de tester la création d'un arbre de décision simple, sans forêt, avec le calcul du gini optimisé à la réduction du nombre de node
// À tester avec TEST_SIMPLE_PENDIGITS à true
#define TEST_SIMPLE_PENDIGITS_WITH_GINI_LESS_NODE false


// |
// | FORET PENDIGITS
// |
// Permet de tester la création d'une forêt d'arbre de décision, avec le calcul du gini (minj+maxj)/2.
#define TEST_PENDIGITS_FOREST true
#define TEST_PENDIGITS_FOREST_TREE_COUNT 40
#define TEST_PENDIGITS_FEATURES_BAGGING true
// Le bagging local est beaucoup plus rapide que le bagging normal, mais un tout petit peu moins précis.
#define TEST_PENDIGITS_LOCAL_FEATURES_BAGGING false
#define TEST_PENDIGITS_INSTANCE_BAGGING true
#define TEST_PENDIGITS_INSTANCE_BAGGING_PROPORTION 0.5f

// |
// | FORET MNIST
// |

#if TEST_SIMPLE_PENDIGITS
int main(int argc, char* args[]) {
    Args.split = USE_GINI_LESS_NODE ? GINI_LESS_NODE : GINI_NORMAL;

    strcpy(Args.trainPath, "../Datasets/PENDIGITS_train.txt");
    strcpy(Args.testPath, "../Datasets/PENDIGITS_test.txt");

    StartTest();

    return 0;
}
#endif 

#if TEST_PENDIGITS_FOREST
int main(int argc, char* args[]) {
	Args.treeCount = TEST_PENDIGITS_FOREST_TREE_COUNT;

	strcpy(Args.trainPath, "../Datasets/PENDIGITS_train.txt");
	strcpy(Args.testPath, "../Datasets/PENDIGITS_test.txt");

    Args.useFeatureBagging = TEST_PENDIGITS_FEATURES_BAGGING;
    Args.useInstanceBagging = TEST_PENDIGITS_INSTANCE_BAGGING;
    Args.instanceBaggingProportion = TEST_PENDIGITS_INSTANCE_BAGGING_PROPORTION;

	StartTest();
	return 0;
}
#endif 

//int main(int argc, char* args[]) {
//   // printf("Dataset\n");
//   // Dataset *trainData = Dataset_readFromFile("../Datasets/MNIST_train.txt");
//   // Dataset *testData = Dataset_readFromFile("../Datasets/MNIST_test.txt");
//
//   // //TransformGrayToWhite(trainData, 20, true, 1, 255);
//   // //TransformGrayToWhite(testData, 20, true, 1, 255);
//
//   // //ApplyMedianFilter(trainData);
//   // //ApplyMedianFilter(testData);
//
//
//   //Dataset_writeToFile(trainData, "../Datasets/MNIST_train_filtered_4.txt");
//   //Dataset_writeToFile(testData, "../Datasets/MNIST_test_filtered_4.txt");
//   //printf("Write ds\n");
//    RandomForest *rf = LoadForestFromFile("../Forests/FOREST_TRAINED_FOR_SDL.dfm");
//    RunSdl(rf);
//    return;
//
//    time_t start = time(NULL);
//
//    strcpy(Args.trainPath, "../Datasets/MNIST_train_filtered_4.txt");
//    strcpy(Args.testPath, "../Datasets/MNIST_test_filtered_4.txt");
//
//    //strcpy(Args.pathForest, "../Forests/MNIST_FILTERED_HYPERPARAMETERS_98_65.dfm");
//    Args.filtersDatasets = false;
//    Args.filters[0] = '0';
//    Args.filters[1] = '1';
//    // Add a second 1 filter improve by 0.03%
//    //Args.filters[2] = '1';
//
//    Args.saveForest = true;
//    strcpy(Args.pathSaveForest, "../Forests/newForestTest.dfm");
//
//    Args.treeCount = 20;
//    Args.useLocalFeatureBagging = true;
//
//
//    StartTest();
//
//    time_t end = time(NULL);
//    printf("Execution time: %d seconds\n", (int)(end - start));
//
//    return 0;
//}