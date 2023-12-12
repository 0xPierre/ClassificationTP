#include "Settings.h"


int main()
{
    Dataset* trainData = Dataset_readFromFile("Datasets/PENDIGITS_train.txt");

    Subproblem* subproblem = Dataset_getSubproblem(trainData);
    Subproblem_print(subproblem);

    Subproblem_destroy(subproblem);
    Dataset_destroy(trainData);
    printf("Process ended successfully\n");

    return 0;
}

