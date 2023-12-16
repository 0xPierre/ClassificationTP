#include <stdlib.h>
#include <stdio.h>
#include "../include/Dataset.h"

int main()
{
    char path[128] = "/home/adrien/Projects/C/ClassificationTP/Datasets/PENDIGITS_train.txt";
    Dataset *trainData = Dataset_readFromFile(path);
    Subproblem *subproblem = Dataset_getSubproblem(trainData);
    Subproblem_print(subproblem);
    Subproblem_destroy(subproblem);
    Dataset_destroy(trainData);
    printf("Hello world");
}

