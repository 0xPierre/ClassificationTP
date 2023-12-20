#include "Settings.h"


DecisionArgs Args = { GINI_NORMAL };

int main(int argc, char* args[]) {

    char train[128] = "../Datasets/MNIST_train.txt";
    char test[128] = "../Datasets/MNIST_test.txt";

    test_datasets_concatenate(train, test);
    //test_datasets_count_white(train, test);
    //RandomForest *rf = LoadForestFromFile("../Forests/MNIST20tree_965.dfm");
    //RunSdl(rf);
//
   /* 
    RandomForest_destroy(rf);*/

//    Args.split = GINI_NORMAL;
//    Args.treeCount = 20;
////
//    Args.useFeatureBagging = true;
//    Args.featureBaggingProportion = 0.8f;
////
//    Args.instanceBaggingProportion = 0.7f;
////
//    strcpy(Args.trainPath, "../Datasets/MNIST_train.txt");
//    strcpy(Args.testPath, "../Datasets/MNIST_test.txt");
//
    //StartTest();

    //char train[128] = "../Datasets/PENDIGITS_train.txt";
    //char test[128] = "../Datasets/PENDIGITS_test.txt";


    //test_random_forest(train, test, 10);
    //test_load_forest(train, test, "../Forests/MNIST50.dfm");


    //char train[128] = "../Datasets/MNIST_train_filtered.txt";
    //char test[128] = "../Datasets/MNIST_test_filtered.txt";
    ////printf("load");
    //test_dump_forest(train, test, "./MNIST_BIGFOREST.txt", 2000);

    //test_datasets_improvement(train, test);

    //test_random_forest(train, test, 5);

    return 0;
}