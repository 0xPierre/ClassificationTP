#include "Settings.h"

void test_split_compute()
{
    Dataset* trainData = Dataset_readFromFile("../Datasets/PENDIGITS_train.txt");

    Subproblem* subproblem = Dataset_getSubproblem(trainData);
    Subproblem_print(subproblem);

    printf("Go on\n");
    Split split = Split_compute(subproblem);
    printf("Split: featureID=%d, threshold=%f\n", split.featureID, split.threshold);


    Subproblem_destroy(subproblem);
    Dataset_destroy(trainData);
    printf("Process ended successfully\n");
}

void test_node_tree_count()
{
    char path[128] = "Datasets/PENDIGITS_train.txt";

    Dataset* trainData = Dataset_readFromFile(path);
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Go on\n");
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.0);

    printf("Generation d'un arbre de %d noeuds\n", Decision_nodeCount(tree));

    DecisionTree_destroy(tree);
    Dataset_destroy(trainData);

    printf("Process ended successfully\n");
}


void test_train_test_evaluation()
{
    char pathTrain[128] = "../Datasets/PENDIGITS_train.txt";
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    char pathTest[128] = "../Datasets/PENDIGITS_test.txt";
    printf("Read test dataset\n");
    Dataset* testData = Dataset_readFromFile(pathTest);
    printf("Get train subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Create decision tree\n");
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.0f);
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
}

void test_Dataset_bagging()
{
    char path[128] = "Datasets/PENDIGITS_train.txt";
    Dataset* trainData = Dataset_readFromFile(path);

    Subproblem* bag = Dataset_bagging(trainData, 0.7f);
    printf("%d instances in the bag\n", bag->instanceCount);

    Subproblem_destroy(bag);
    Dataset_destroy(trainData);
    printf("Process ended successfully\n");
}

void test_random_forest()
{
    char pathTrain[128] = "Datasets/PENDIGITS_train.txt";
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    printf("Read test dataset\n");
    char pathTest[128] = "Datasets/PENDIGITS_test.txt";
    Dataset* testData = Dataset_readFromFile(pathTest);
    printf("Get subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Create random forest\n");
    RandomForest* rf = RandomForest_create(20, trainData, 30, 0.5f, 1.0f);
    printf("Evaluate train\n");
    float scoreTrain = RandomForest_evaluate(rf, trainData);
    printf("Evaluate test\n");
    float scoreTest = RandomForest_evaluate(rf, testData);
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);

    RandomForest_destroy(rf);
    Dataset_destroy(trainData);
    Dataset_destroy(testData);
    Subproblem_destroy(sp);
}

void test_memory()
{
    char pathTrain[128] = "Datasets/PENDIGITS_train.txt";
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    char pathTest[128] = "Datasets/PENDIGITS_test.txt";
    printf("Read test dataset\n");
    Dataset* testData = Dataset_readFromFile(pathTest);
    printf("Get train subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Create decision tree\n");
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, .11f);
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
}


void vpl_test(char pathTrain[128], char pathTest[128])
{
    //Dataset* trainData = Dataset_readFromFile(pathTrain);
    //char pathTest[128] = "Datasets/PENDIGITS_test.txt";
    //Dataset* testData = Dataset_readFromFile(pathTest);
    //Subproblem* sp = Dataset_getSubproblem(trainData);
    //DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.0);
    //float scoreTrain = DecisionTree_evaluate(tree, trainData);
    //printf("Evaluation of the tree with test\n");
    //float scoreTest = DecisionTree_evaluate(tree, testData);
    //printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);
    //Subproblem_destroy(sp);
    //DecisionTree_destroy(tree);
    //Dataset_destroy(trainData);
    //Dataset_destroy(testData);
}

void test_dump_forest()
{
    char pathTrain[128] = "Datasets/PENDIGITS_train.txt";
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    printf("Get subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Create random forest\n");
    RandomForest* rf = RandomForest_create(5, trainData, 30, 0.5f, 1.0f);


    ForestFileDump(rf, "Forests/PENDIGITS.dfm");
    RandomForest* rf2 = LoadForestFromFile("Forests/PENDIGITS.dfm");

    float scoreTrain = RandomForest_evaluate(rf, trainData);
    printf("Score train : %f\n", scoreTrain);
    float score2Train = RandomForest_evaluate(rf2, trainData);
    printf("Score train imported : %f\n", scoreTrain);

    RandomForest_destroy(rf);
    RandomForest_destroy(rf2);
    Dataset_destroy(trainData);
    Subproblem_destroy(sp);
}