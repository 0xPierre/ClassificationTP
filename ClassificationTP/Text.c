#include "Settings.h"

void Text_New(Text settings, SDL_Renderer *renderer) {

    if (renderer == NULL) {
        fprintf(stderr, "Error: Renderer is NULL\n");
        exit(EXIT_FAILURE);
    }

    // Initialize SDL_ttf if not already initialized
    if (TTF_WasInit() == 0) {
        if (TTF_Init() != 0) {
            fprintf(stderr, "Error initializing SDL_ttf: %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
        }
    }

    // Load font and create text surface
    TTF_Font *font = TTF_OpenFont("../Assets/Fonts/Roboto-Regular.ttf", settings.fontSize);
    if (font == NULL) {
        fprintf(stderr, "Error loading font: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Set colors
    SDL_Color textColor = {
            settings.color.r,
            settings.color.g,
            settings.color.b
    };
    SDL_Surface *textSurf = TTF_RenderText_Solid(font, settings.label, textColor);
    if (textSurf == NULL) {
        fprintf(stderr, "Error creating text surface: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        exit(EXIT_FAILURE);
    }

    // Create texture from surface and set position
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
    if (textTexture == NULL) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurf);  // Cleanup
        TTF_CloseFont(font);       // Cleanup
        exit(EXIT_FAILURE);
    }
    SDL_Rect textRect = {settings.x, settings.y, settings.recWidth, settings.rectHeight};

    // Cleanup
    SDL_FreeSurface(textSurf);
    TTF_CloseFont(font);

    // Render Text
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
}