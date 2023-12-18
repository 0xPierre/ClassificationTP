#include "Settings.h"

int main(int argc, char **argv) {

    double start = omp_get_wtime();

    //test_split_compute();
    //test_node_tree_count();
    //test_train_test_evaluation();
    //test_Dataset_bagging();
    test_random_forest();
    /*test_memory();*/
    //test_dump_forest();


    double end = omp_get_wtime();
    printf("Work took %f seconds\n", end - start);

    return 0;
}

