#include "Settings.h"

// Merci de descendre juste en dessous pour avoir acc�s aux diff�rents configurations possibles.
// Et pas au niveau de la structure
//DecisionArgs Args = {
//    .split = SPLIT_NORMAL,
//    .gini = GINI_NORMAL,
//    .featureBaggingProportion = 1.f,
//    .enableSigmoid = false,
//    .useFeatureBagging = false,
//    .useLocalFeatureBagging = false,
//    .instanceBaggingProportion = 1.f, // Ne pas modifier
//    .useInstanceBagging = false, // Ne pas modifier
//    .isSilent = false,
//    .prunningThreshold = 1.f,
//    .treeCount = 1,
//    .maxDepth = 30,
//    .pathForest = "",
//    .trainPath = NULL,
//    .testPath = NULL,
//    .filters = "\0",
//    .filtersDatasets = false,
//    .pathSaveForest = NULL,
//    .saveForest = false,
//    .isInVPL = false
//};

// Bonjour, voici les diff�rents configuration possibles permettant de tester notre travail.
// Pour tester une configuration, il suffit de mettre la valeur � true et de lancer le programme.
// Attention, merci d'au moins mettre le premier define de chaque paquet � false si ce n'est pas celui s�lectionner.

// Permet de tester la cr�ation d'un arbre de d�cision simple, sans for�t, avec le calcul du gini (minj+maxj)/2.
#define TEST_SIMPLE_PENDIGITS false


// Permet de tester la cr�ation d'un arbre de d�cision simple, sans for�t, avec le calcul du gini optimis� � la r�duction du nombre de node
// � tester avec TEST_SIMPLE_PENDIGITS � true
#define TEST_SIMPLE_PENDIGITS_WITH_GINI_LESS_NODE false


// |
// | FORET PENDIGITS
// |
// Permet de tester la cr�ation d'une for�t d'arbre de d�cision, avec le calcul du gini (minj+maxj)/2.
#define TEST_PENDIGITS_FOREST false
#define TEST_PENDIGITS_FOREST_TREE_COUNT 40
#define TEST_PENDIGITS_FEATURES_BAGGING true
// Le bagging local est beaucoup plus rapide que le bagging normal, mais un tout petit peu moins pr�cis.
// Beaucoup moins de Node
#define TEST_PENDIGITS_LOCAL_FEATURES_BAGGING false
#define TEST_PENDIGITS_INSTANCE_BAGGING true
#define TEST_PENDIGITS_INSTANCE_BAGGING_PROPORTION 0.5f

// |
// | Run SDL
// |
#define TEST_SDL false
#define TEST_SDL_FOREST_PATH "../Forests/FOREST_TRAINED_FOR_SDL.dfm"

// |
// | RandomForest MNIST
// |
#define TEST_MNIST_RANDOM_FOREST false
#define TEST_MNIST_RANDOM_FOREST_TRAIN_PATH "../Datasets/MNIST_train.txt"
#define TEST_MNIST_RANDOM_FOREST_TEST_PATH "../Datasets/MNIST_test.txt"
#define TEST_MNIST_RANDOM_FOREST_USE_FILTERS true
#define TEST_MNIST_RANDOM_FOREST_USE_LOCAL_FEATURES_BAGGING true
#define TEST_MNIST_RANDOM_FOREST_USE_FEATURES_BAGGING false
#define TEST_MNIST_RANDOM_FOREST_TREE_COUNT 20

// |
// | MNIST 98.7
// |
#define TEST_BEST_MNIST false
#define TEST_BEST_MNIST_FOREST_PATH "../Forests/MNIST_FILTERED_HYPERPARAMETERS_98_65.dfm"
#define TEST_BEST_MNIST_TRAIN_PATH "../Datasets/MNIST_train_filtered.txt"
#define TEST_BEST_MNIST_TEST_PATH "../Datasets/MNIST_test_filtered.txt"

// |
// | MNIST TEST passage sous 32ko pour arduino
// |
#define TEST_LOW_MNIST false
#define TEST_LOW_MNIST_TRAIN_PATH "../Datasets/MNIST_train_filtered.txt"
#define TEST_LOW_MNIST_TEST_PATH "../Datasets/MNIST_test_filtered.txt"
#define TEST_LOW_MNIST_SAVE_FOREST "../Forests/MNIST_LOW.dfm"

// |
// | VPL
// |
#define VPL_TEST false

#if VPL_TEST
int main(int argc, char* args[]) {
    Args.isSilent = false;
    Args.isInVPL = false;
    Args.useLocalFeatureBagging = true;
    //Args.useFeatureBagging = true;
    strcpy(Args.trainPath, args[1]);
    strcpy(Args.testPath, args[2]);
    Args.treeCount = 50;
    StartTest();
}
#endif

#if TEST_LOW_MNIST
int main(int argc, char* args[]) {
    time_t start = time(NULL);

    Args.treeCount = 10;
    strcpy(Args.testPath, TEST_LOW_MNIST_TEST_PATH);
    strcpy(Args.trainPath, TEST_LOW_MNIST_TRAIN_PATH);
    Args.useLocalFeatureBagging = true;

    Args.filtersDatasets = true;
    Args.filters[0] = '0';
    Args.filters[1] = '1';

    Args.saveForest = true;
    strcpy(Args.pathSaveForest, TEST_LOW_MNIST_SAVE_FOREST);

    StartTest();
    time_t end = time(NULL);
    printf("Execution time: %d seconds\n", (int)(end - start));

    return 0;
}
#endif

#if TEST_SIMPLE_PENDIGITS
int main(int argc, char* args[]) {
    //Args.split = TEST_SIMPLE_PENDIGITS_WITH_GINI_LESS_NODE ? GINI_LESS_NODE : GINI_NORMAL;

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

#if TEST_SDL
int main(int argc, char* argv[]) {
    RandomForest* rf = LoadForestFromFile(TEST_SDL_FOREST_PATH);
    RunSdl(rf);

    return 0;
}
#endif

#if TEST_MNIST_RANDOM_FOREST
int main(int argc, char* argv[]) {
    time_t start = time(NULL);

    Args.treeCount = TEST_MNIST_RANDOM_FOREST_TREE_COUNT;
    strcpy(Args.testPath, TEST_MNIST_RANDOM_FOREST_TEST_PATH);
    strcpy(Args.trainPath, TEST_MNIST_RANDOM_FOREST_TRAIN_PATH);
    Args.useLocalFeatureBagging = TEST_MNIST_RANDOM_FOREST_USE_LOCAL_FEATURES_BAGGING;
    Args.useFeatureBagging = TEST_MNIST_RANDOM_FOREST_USE_FEATURES_BAGGING;

    Args.filtersDatasets = TEST_MNIST_RANDOM_FOREST_USE_FILTERS;
    Args.filters[0] = '0';
    Args.filters[1] = '1';

    StartTest();
    time_t end = time(NULL);
    printf("Execution time: %d seconds\n", (int)(end - start));

    return 0;
}
#endif

#if TEST_BEST_MNIST
int main(int argc, char* argv[]) {
    time_t start = time(NULL);

    strcpy(Args.pathForest, TEST_BEST_MNIST_FOREST_PATH);
    strcpy(Args.testPath, TEST_BEST_MNIST_TEST_PATH);
    strcpy(Args.trainPath, TEST_BEST_MNIST_TRAIN_PATH);

    StartTest();
    time_t end = time(NULL);
    printf("Execution time: %d seconds\n", (int)(end - start));

    return 0;
}
#endif

//#if TEST_BEST_MNIST_LOW_NODE

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