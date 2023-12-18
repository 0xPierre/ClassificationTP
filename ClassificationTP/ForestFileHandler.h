#pragma once
#include "Settings.h"

void ForestFileDump(RandomForest* rf, char path[128]);

RandomForest* LoadForestFromFile(char path[128]);