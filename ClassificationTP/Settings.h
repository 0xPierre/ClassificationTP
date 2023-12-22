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
#include "time.h"
#include "Split.h"
#include "DecisionTree.h"
#include "RandomForest.h"
#include "ForestFileHandler.h"
#include "DatasetImprovement.h"
#include "Interface.h"
#include "string.h"
#include "math.h"
#include "Tests.h"
#include "HyperParameters.h"
#include "Text.h"
#include "Sound.h"
#include <omp.h>


#define AssertNew(ptr) { if (ptr == NULL) { assert(false); abort(); } }


enum SplitType {
    GINI_NORMAL,
    GINI_LESS_NODE,
};

typedef struct sDecisionArgs {
    int treeCount;
    int maxDepth;
    enum SplitType split;

    bool useLocalFeatureBagging;
    bool useFeatureBagging;
    float featureBaggingProportion;

    bool useInstanceBagging;
    float instanceBaggingProportion;

    char trainPath[128];
    char testPath[128];

    bool isSilent;
    int prunningThreshold;

    char pathForest[128];

    // List of fitlers to apply
    // 0 = Gray To White
    // 1 = Median
    char filters[128];
    bool filtersDatasets;

    bool saveForest;
    char pathSaveForest[128];

} DecisionArgs;

extern DecisionArgs Args;