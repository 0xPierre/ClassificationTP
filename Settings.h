#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "Dataset.h"
#include "Split.h"
#include "DecisionTree.h"
#include "RandomForest.h"
#include "ForestFileHandler.h"


#define AssertNew(ptr) { if (ptr == NULL) { assert(false); abort(); } }