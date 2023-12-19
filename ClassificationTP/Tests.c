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

void test_node_tree_count(char *pathTrain)
{

    Dataset* trainData = Dataset_readFromFile(pathTrain);
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Go on\n");
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.0);

    printf("Generation d'un arbre de %d noeuds\n", Decision_nodeCount(tree));

    DecisionTree_destroy(tree);
    Dataset_destroy(trainData);

    printf("Process ended successfully\n");
}


void test_train_test_evaluation(char *pathTrain, char *pathTest)
{
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
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

void test_random_forest(char pathTrain[128], char pathTest[128], int treeCount)
{
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    printf("Read test dataset\n");
    Dataset* testData = Dataset_readFromFile(pathTest);
    printf("Get subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Create random forest\n");
    RandomForest* rf = RandomForest_create(treeCount, trainData, 30, 0.6f, 1.f);
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
    char pathTrain[128] = "../Datasets/MNIST_train.txt";
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    printf("Get subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Create random forest\n");
    RandomForest* rf = RandomForest_create(5, trainData, 30, 0.5f, 1.0f);


    ForestFileDump(rf, "../Forests/MNIST3.dfm");
    RandomForest* rf2 = LoadForestFromFile("../Forests/MNIST3.dfm");

    float scoreTrain = RandomForest_evaluate(rf, trainData);
    printf("Score train : %f\n", scoreTrain);
    float score2Train = RandomForest_evaluate(rf2, trainData);
    printf("Score train imported : %f\n", scoreTrain);

    RandomForest_destroy(rf);
    RandomForest_destroy(rf2);
    Dataset_destroy(trainData);
    Subproblem_destroy(sp);
}

void test_load_forest(char pathTrain[128], char pathTest[128], char pathForest[128])
{
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    printf("Read test dataset\n");
    Dataset* testData = Dataset_readFromFile(pathTest);
    RandomForest* rf2 = LoadForestFromFile(pathForest);

    float scoreTrain = RandomForest_evaluate(rf2, trainData);
    printf("Score train : %f\n", scoreTrain);
    float scoreTest = RandomForest_evaluate(rf2, testData);
    printf("Score test randomforest imported : %f\n", scoreTest);
}



void test_datasets_improvement(char* pathTrain, char* pathTest)
{
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    printf("Update train\n");

    printf("Read test dataset\n");
    printf("Update train\n");
    Dataset* testData = Dataset_readFromFile(pathTest);

    /*printf("Get subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Create decision tree\n");
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.0f);
    printf("Generation d'un arbre de %d noeuds\n", Decision_nodeCount(tree));
    printf("Evaluation of the tree with train\n");
    float scoreTrain = DecisionTree_evaluate(tree, trainData);
    printf("Evaluation of the tree with test\n");
    float scoreTest = DecisionTree_evaluate(tree, testData);
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);*/

    //printf("20\n");

    // print les features de l'instance 0
    TransformGrayToWhite(trainData, 20, true, 1, 255);
    TransformGrayToWhite(testData, 20, true, 1, 255);

    ApplyMedianFilter(trainData);
    ApplyMedianFilter(testData);

    /*Dataset_writeToFile(trainData, "../Datasets/MNIST_train_filtered.txt");
    Dataset_writeToFile(testData, "../Datasets/MNIST_test_filtered.txt");
    return;*/


    printf("Get subproblem\n");
    Subproblem* sp2 = Dataset_getSubproblem(trainData);
    printf("Create decision tree\n");
    DecisionTreeNode* tree2 = DecisionTree_create(sp2, 0, 30, 1.0f);
    printf("Generation d'un arbre de %d noeuds\n", Decision_nodeCount(tree2));
    printf("Evaluation of the tree with train\n");
    float scoreTrain2 = DecisionTree_evaluate(tree2, trainData);
    printf("Evaluation of the tree with test\n");
    float scoreTest2 = DecisionTree_evaluate(tree2, testData);
    printf("train = %.3f, test = %.3f\n", scoreTrain2, scoreTest2);

    Subproblem_destroy(sp2);
    DecisionTree_destroy(tree2);
    Dataset_destroy(trainData);
    Dataset_destroy(testData);
}


//void test_randforest_improvement()