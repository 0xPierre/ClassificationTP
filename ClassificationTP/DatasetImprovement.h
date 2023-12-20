#pragma once
#include "Settings.h"

/*
Return a new dataset with a feature containing the number of white pixels
*/
Dataset* DatasetCountWhite(Dataset* dataset);


/*
Transform the gray pixels to white or black/shade
*/
void TransFormGrayToWhiteOneFeature(int* values, int featureCount, int threshold, bool setToMin, int min, int max);

/*
Transform the gray pixels to white or black
@param threshold: the threshold to transform the pixels
@param setToMin: if true, the pixels below the threshold will be set to min
@param min: the value to set the pixels below the threshold
@param max: the value to set the pixels above the threshold
*/
void TransformGrayToWhite(Dataset* dataset, int threshold, bool setToMin, int min, int max);


/*
Used to apply a median filter to the dataset
*/
void ApplyMedianFilter(Dataset* dataset);

