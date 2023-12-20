//
// Created by adrien on 12/20/23.
//
#pragma once
#include "Settings.h"

#ifndef CLASSIFICATIONTP_TEXT_H
#define CLASSIFICATIONTP_TEXT_H

typedef struct sColor {
    int r;
    int g;
    int b;
} Color;

typedef struct sText {
    char label[100];
    int x;
    int y;
    int recWidth;
    int rectHeight;
    int fontSize;
    Color color;
} Text;

#endif //CLASSIFICATIONTP_TEXT_H


void Text_New(Text settings, SDL_Renderer *renderer);