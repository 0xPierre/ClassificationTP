#include "Settings.h"

void test_split_compute()
{
    Dataset* trainData = Dataset_readFromFile("../Datasets/PENDIGITS_train.txt");

    Subproblem* subproblem = Dataset_getSubproblem(trainData);
    Subproblem_print(subproblem);

    printf("Go on\n");
    Split split = Split_compute(subproblem, NULL);
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
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.0, NULL);

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
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.0f, NULL);
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
    RandomForest* rf = RandomForest_create(treeCount, trainData, 25, Args.instanceBaggingProportion, Args.prunningThreshold);
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
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, .11f, NULL);
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

void test_datasets_concatenate(char pathTrain[128], char pathTest[128]) {
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    Dataset* trainData2 = CopyDataset(trainData);

    printf("Filter train\n");
    TransformGrayToWhite(trainData2, 20, true, 1, 255);
    ApplyMedianFilter(trainData2);

    printf("Concatenate train\n");
    Dataset *trainDataBig = ConcatenateTwoDatasetFeatures(trainData, trainData2);

    printf("Read test dataset\n");
    Dataset* testData = Dataset_readFromFile(pathTest);
    Dataset* testData2 = CopyDataset(testData);
    printf("Filter test\n");
    TransformGrayToWhite(testData2, 20, true, 1, 255);
    ApplyMedianFilter(testData2);

    Dataset *testDataBig = ConcatenateTwoDatasetFeatures(testData, testData2);


    printf("%d %d %d %d\n", trainDataBig->featureCount, trainDataBig->instanceCount, testDataBig->featureCount, testDataBig->instanceCount);

    printf("Get train subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(trainDataBig);
    printf("Create decision tree\n");
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.f, NULL);
    printf("Generation d'un arbre de %d noeuds\n", Decision_nodeCount(tree));
    printf("Evaluation of the tree with train\n");
    float scoreTrain = DecisionTree_evaluate(tree, trainDataBig);
    printf("Evaluation of the tree with test\n");
    float scoreTest = DecisionTree_evaluate(tree, testDataBig);
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);

    printf("Get train subproblem\n");
    Subproblem* sp1 = Dataset_getSubproblem(trainData);
    printf("Create decision tree\n");
    DecisionTreeNode* tree1 = DecisionTree_create(sp1, 0, 30, 1.f, NULL);
    printf("Generation d'un arbre de %d noeuds\n", Decision_nodeCount(tree1));
    printf("Evaluation of the tree with train\n");
    scoreTrain = DecisionTree_evaluate(tree1, trainData);
    printf("Evaluation of the tree with test\n");
    scoreTest = DecisionTree_evaluate(tree1, testData);
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);

    printf("Get train subproblem\n");
    Subproblem* sp2 = Dataset_getSubproblem(trainData2);
    printf("Create decision tree\n");
    DecisionTreeNode* tree2 = DecisionTree_create(sp2, 0, 30, 1.f, NULL);
    printf("Generation d'un arbre de %d noeuds\n", Decision_nodeCount(tree2));
    printf("Evaluation of the tree with train\n");
    scoreTrain = DecisionTree_evaluate(tree2, trainData2);
    printf("Evaluation of the tree with test\n");
    scoreTest = DecisionTree_evaluate(tree2, testData2);
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);

    Subproblem_destroy(sp);
    Subproblem_destroy(sp1);
    Subproblem_destroy(sp2);
    DecisionTree_destroy(tree);
    DecisionTree_destroy(tree1);
    DecisionTree_destroy(tree2);

    Dataset_destroy(trainDataBig);
    Dataset_destroy(trainData2);
    Dataset_destroy(trainData);

    Dataset_destroy(testData);
    Dataset_destroy(testData2);
    Dataset_destroy(testDataBig);
}

void test_datasets_count_white(char pathTrain[128], char pathTest[128]) {
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    trainData = DatasetCountWhite(trainData);
    printf("%d %d\n", trainData->featureCount, trainData->instanceCount);
   
 //   // printf the first instrance values
 //   printf("Class : %d\n", trainData->instances[0].classID);
 //   for (int i = 0; i < trainData->featureCount; i++)
 //   {
	//	printf("%d ", trainData->instances[0].values[i]);
	//}

    printf("Read test dataset\n");
    Dataset* testData = Dataset_readFromFile(pathTest);
    testData = DatasetCountWhite(testData);
    printf("Get train subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Create decision tree\n");
    DecisionTreeNode* tree = DecisionTree_create(sp, 0, 30, 1.f, NULL);
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
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    Dataset* testData = Dataset_readFromFile(pathTrain);

    Subproblem* sp = Dataset_getSubproblem(trainData);
    Subproblem_destroy(sp);

    RandomForest * rf = RandomForest_create(17, trainData, 25, 0.5f, 1.0f);
    
    for (int i = 0; i < testData->instanceCount; i++) {
        int classId = RandomForest_predict(rf, &testData->instances[i]);
        printf("%d\n", classId);
    }

    Dataset_destroy(trainData);
    Dataset_destroy(testData);
    RandomForest_destroy(rf);
}

void test_dump_forest(char pathTrain[128], char pathTest[128], int treeCount)
{
    printf("Read train dataset\n");
    Dataset* trainData = Dataset_readFromFile(pathTrain);
    printf("Get subproblem\n");
    Subproblem* sp = Dataset_getSubproblem(trainData);
    printf("Create random forest\n");
    RandomForest* rf = RandomForest_create(treeCount, trainData, 30, 0.5f, 1.0f);


    ForestFileDump(rf, "./MNIST_BIGFOREST.txt");
    RandomForest* rf2 = LoadForestFromFile("./MNIST_BIGFOREST.txt");

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
    DecisionTreeNode* tree2 = DecisionTree_create(sp2, 0, 30, 1.0f, NULL);
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


void StartTest() {
    if (Args.treeCount <= 0) {
        printf("Error : treeCount must be > 0\n");
        assert(false);
    }

    if (Args.treeCount > 1) {
        test_random_forest(Args.trainPath, Args.testPath, Args.treeCount);
    }
    else {
        test_train_test_evaluation(Args.trainPath, Args.testPath);
    }
}