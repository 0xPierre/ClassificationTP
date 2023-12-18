#include "Settings.h"



void dumpForest(char path[128]) {
    printf("Read data\n");
    Dataset* data = Dataset_readFromFile(path);
    printf("Get subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(data);
    printf("Create random forest\n");
    RandomForest* rf = RandomForest_create(1, data, 30, 1.f, 1.0f);
    ForestFileDump(rf, "Forests/MNIST.dfm");


    RandomForest_destroy(rf);
    Dataset_destroy(data);
    Subproblem_destroy(sp);
}


int main(int argc, char** argv)
{
    //test_split_compute();
    //test_node_tree_count();
    //test_train_test_evaluation();
    //test_Dataset_bagging();
    //test_random_forest();
    /*test_memory();*/
    //test_dump_forest();

    //dumpForest("Datasets/MNIST_train.txt");

    /*RandomForest * rf = LoadForestFromFile("Forests/MNIST.dfm");
    Dataset* data = Dataset_readFromFile("Datasets/MNIST_test.txt");

    float a = RandomForest_evaluate(rf, data);
    printf("Score : %f\n", a);

    RandomForest_destroy(rf);*/

    test_train_test_evaluation();
    test_random_forest();

    return 0;
}

