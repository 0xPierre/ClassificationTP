#include "Settings.h"


int main(int argc, char** argv)
{
    /*Dataset* trainData = Dataset_readFromFile("Datasets/PENDIGITS_train.txt");

    Subproblem* subproblem = Dataset_getSubproblem(trainData);
    Subproblem_print(subproblem);

    printf("Go on\n");
    Split split = Split_compute(subproblem);
    printf("Split: featureID=%d, threshold=%f\n", split.featureID, split.threshold);


    Subproblem_destroy(subproblem);
    Dataset_destroy(trainData);
    printf("Process ended successfully\n");

    return 0;*/

    /*char path[128] = "Datasets/PENDIGITS_train.txt";

    Dataset* trainData = Dataset_readFromFile(path);
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Go on\n");
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.0);

    printf("Generation d'un arbre de %d noeuds\n", Decision_nodeCount(tree));

    DecisionTree_destroy(tree);
    Dataset_destroy(trainData);

    printf("Process ended successfully\n");

    return 0;*/

    char pathTrain[128] = "Datasets/PENDIGITS_train.txt";
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    char pathTest[128] = "Datasets/PENDIGITS_test.txt";
    printf("Read test dataset\n");
    Dataset* testData = Dataset_readFromFile(pathTest);
    printf("Get train subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Create decision tree\n");
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.0);
    printf("Generation d'un arbre de %d noeuds\n", Decision_nodeCount(tree));
    printf("Evaluation of the tree with train\n");
    float scoreTrain = DecisionTree_evaluate(tree, trainData);
    printf("Evaluation of the tree with test\n");
    float scoreTest = DecisionTree_evaluate(tree, testData);
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);
    Subproblem_destroy(sp);
    DecisionTree_destroy(tree);
    Dataset_destroy(trainData);
    Dataset_destroy(testData);
    printf("Process ended successfully\n");

    return 0;
}

