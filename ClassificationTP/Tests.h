#pragma once
#include "Settings.h"

void test_split_compute();

void test_node_tree_count(char *pathTrain);

void test_train_test_evaluation(char* pathTrain, char* pathTest);

void test_Dataset_bagging();

void test_random_forest(char pathTrain[128], char pathTest[128], int treeCount);

void test_memory();

void vpl_test(char pathTrain[128], char pathTest[128]);

void test_dump_forest(char pathTrain[128], char pathTest[128], int treeCount);

void test_load_forest(char pathTrain[128], char pathTest[128], char pathForest[128]);

void test_datasets_improvement();

void StartTest();

void test_datasets_count_white(char pathTrain[128], char pathTest[128]);