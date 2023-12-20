#include "Settings.h"


int main(int argc, char* args[]) {

    RandomForest *rf = LoadForestFromFile("../Forests/MNIST50.dfm");

    RunSdl(rf);
    RandomForest_destroy(rf);

    //char train[128] = "../Datasets/MNIST_train.txt";
    //char test[128] = "../Datasets/MNIST_test.txt";
    //////forest

    ////test_random_forest(train, test, 20);
    //test_load_forest(train, test, "../Forests/MNIST50.dfm");


//    char train[128] = "../Datasets/PENDIGITS_train.txt";
//    char test[128] = "../Datasets/PENDIGITS_test.txt";
//
//    //test_datasets_improvement(train, test);
//
//    test_random_forest(train, test, 20);
//    test_dump_forest(train, test, 2000);
//    test_load_forest(train, test, "../Forests/MNIST3-PIERRE.dfm");

    return 0;
}