#include "Settings.h"


int main(int argc, char** argv)
{
    Dataset* trainData = Dataset_readFromFile("Datasets/PENDIGITS_train.txt");

    Subproblem* subproblem = Dataset_getSubproblem(trainData);
    Subproblem_print(subproblem);

    printf("Go on\n");
    Split split = Split_compute(subproblem);
    printf("Split: featureID=%d, threshold=%f\n", split.featureID, split.threshold);


    Subproblem_destroy(subproblem);
    Dataset_destroy(trainData);
    printf("Process ended successfully\n");

    return 0;

    /*char path[128] = "Datasets/PENDIGITS/PENDIGITS_train.txt";

    Dataset* trainData = Dataset_readFromFile(path);
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Go on\n");
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.0);

    printf("Génération d'un arbre de %d noeds\n", Decision_nodeCount(tree));

    DecisionTree_destroy(tree);
    Dataset_destroy(trainData);

    printf("Process ended successfully\n");

    return 0;*/
}

