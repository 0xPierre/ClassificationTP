#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define THREADS 4

#ifdef _WIN32
#  include "SDL.h"
#  include "SDL_image.h"
#  include "SDL_ttf.h"
#  include "SDL_mixer.h"
#else
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
#  include <SDL2/SDL_ttf.h>
//#  include <SDL2/SDL_mixer.h>
#endif

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
#include "DatasetImprovement.h"
#include "Interface.h"
#include "string.h"
#include "math.h"
#include "Tests.h"
#include "Text.h"
#include <omp.h>


#define AssertNew(ptr) { if (ptr == NULL) { assert(false); abort(); } }


enum SplitType {
    GINI_NORMAL,
    GINI_LESS_NODE,
};

typedef struct sDecisionArgs {
    int treeCount;
    enum SplitType split;

    bool useFeatureBagging;
    float featureBaggingProportion;

    bool useInstanceBagging;
    float instanceBaggingProportion;

    char trainPath[128];
    char testPath[128];
} DecisionArgs;

extern DecisionArgs Args;