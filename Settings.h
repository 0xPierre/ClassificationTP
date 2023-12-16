#pragma once
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

#define AssertNew(ptr) { if (ptr == NULL) { assert(false); abort(); } }

#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "Dataset.h"
#include "Split.h"
#include "DecisionTree.h"
#include "RandomForest.h"
#include "ForestFileHandler.h"