#pragma once
#include "Settings.h"


typedef struct sInput {
	// SDL_BUTTON_LEFT or SDL_BUTTON_RIGHT
	bool isMouseClick;
	int mouseButton;
	int mouseX, mouseY;
	bool quit;
} Input;

SDL_Window* initSDL();

void drawPainterPixel(SDL_Renderer* renderer, int x, int y, int color);
/**
* This function allows to run the interface using SDL.
*/
void RunSdl();