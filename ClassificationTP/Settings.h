#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define THREADS 8

// POWER MODE
// Can take : "efficient" | "performance"
#define POWER_MODE() "performance"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "SDL.h"
#include "Dataset.h"
#include "Split.h"
#include "DecisionTree.h"
#include "RandomForest.h"
#include "ForestFileHandler.h"
#include "Tests.h"
#include "Interface.h"
#include "string.h"
#include "math.h"
#include <omp.h>


#define AssertNew(ptr) { if (ptr == NULL) { assert(false); abort(); } }