#pragma once
#include "Settings.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 560
#define PAINT_RECT_SIZE 560
#define FEATURES_COUNT 28
#define IMAGE_PIXEL_SIZE (PAINT_RECT_SIZE / FEATURES_COUNT)

typedef struct sInput {
	bool isMouseClick;
	// SDL_BUTTON_LEFT or SDL_BUTTON_RIGHT or SDL_MIDDLE_CLICK
	int mouseButton;
	int mouseX, mouseY;
	bool quit;
} Input;


typedef struct sButton {
    char label[20];
    int x;
    int y;
    float size;
} Button;

SDL_Rect  AddButton(Button button, SDL_Renderer* renderer);

/*
Init the SDL
*/
SDL_Window* initSDL();


/*
This function allows to update the matrix of pixels depending on the mouse position
*/
void updatePaintMatrix(Input input, int matrix[FEATURES_COUNT][FEATURES_COUNT]);

/*
Used to draw a rect used as a pixel in the paint mode
*/
void drawPainterPixel(SDL_Renderer* renderer, int x, int y, int color);

/**
* This function allows to run the interface using SDL.
*/
void RunSdl(RandomForest* rf);