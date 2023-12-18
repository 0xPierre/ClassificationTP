#pragma once
#define _CRT_SECURE_NO_WARNINGS

// POWER MODE
// Can take : "efficient" | "performance"
#define POWER_MODE() "efficient"

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
#include "Tests.h"
#include "string.h"
#include "math.h"


#define AssertNew(ptr) { if (ptr == NULL) { assert(false); abort(); } }