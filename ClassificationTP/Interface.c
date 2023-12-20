#include "Settings.h"


const int images_shade_of_white[] = {10, 50, 80, 120, 190, 220};
int clicked = 0;

SDL_Window *initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't intialize SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow("Paint AI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("COund't create window SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    return window;
}

void drawPainterPixel(SDL_Renderer *renderer, int x, int y, int color) {
    SDL_SetRenderDrawColor(renderer, color, color, color, 255);

    SDL_Rect rect;
    rect.x = IMAGE_PIXEL_SIZE * x;
    rect.y = IMAGE_PIXEL_SIZE * y;
    rect.w = IMAGE_PIXEL_SIZE;
    rect.h = IMAGE_PIXEL_SIZE;

    SDL_RenderFillRect(renderer, &rect);
}


Input getInputs() {
    SDL_Event event;
    Input input = {.isMouseClick = false, .quit = false};

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_MOUSEMOTION : {
                if (event.button.button != SDL_BUTTON_MIDDLE) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    input.isMouseClick = event.button.button > 0;
                    input.mouseButton = event.button.button;
                    input.mouseX = mouseX;
                    input.mouseY = mouseY;
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                input.isMouseClick = true;
                input.mouseButton = event.button.button;
                input.mouseX = mouseX;
                input.mouseY = mouseY;
                clicked = true;
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                printf("MOUSE UP\n");
                input.isMouseClick = false;
                clicked = false;
                break;
            }
        }

        if (event.type == SDL_QUIT) {
            input.quit = true;
        }
    }

    return input;
}

void applyConvolution(int matrix[FEATURES_COUNT][FEATURES_COUNT], int x, int y) {
    if (x >= FEATURES_COUNT || y >= FEATURES_COUNT || x < 0 || y < 0) return;
    int sum = 0;
    int sumXY = 0;

    for (int x1 = -1; x1 < 2; x1++) {
        int xt = (x + x1);

        if (xt < 0 || xt >= FEATURES_COUNT) continue;
        for (int y1 = -1; y1 < 2; y1++) {
            int yt = (y + y1);
            if (yt < 0 || yt >= FEATURES_COUNT) continue;
            sum += matrix[xt][yt];
            sumXY++;
        }
    }

    if (matrix[x][y] != 255)
        matrix[x][y] = (sum / sumXY);
}

void applyBrush(int matrix[FEATURES_COUNT][FEATURES_COUNT], float x, float y, int brushSize) {
    if (x < 0 || x >= FEATURES_COUNT || y < 0 || y >= FEATURES_COUNT) return;

    if (brushSize < 1) return;

    float startX = (x - brushSize < 0) ? 0 : x - brushSize;
    float startY = (y - brushSize < 0) ? 0 : y - brushSize;
    float endX = (x + brushSize >= FEATURES_COUNT) ? FEATURES_COUNT - 1 : x + brushSize;
    float endY = (y + brushSize >= FEATURES_COUNT) ? FEATURES_COUNT - 1 : y + brushSize;
    for (float i = startX; i <= endX; ++i) {
        for (float j = startY; j <= endY; ++j) {
            float distanceSquared = (x - i) * (x - i) + (y - j) * (y - j);
            int intensity = 255 - ((int) distanceSquared * 255) / (brushSize * brushSize);

            intensity = (intensity < 0) ? 0 : (intensity > 255) ? 255 : intensity;

            matrix[(int) i][(int) j] = fmax(intensity, matrix[(int) i][(int) j]);
        }
    }
}

void updatePaintMatrix(Input input, int matrix[FEATURES_COUNT][FEATURES_COUNT], int typeOfBrush) {
    if (!clicked) {
        stopMusics();
        return;
    }


    int x = (int) ((float) input.mouseX * (float) FEATURES_COUNT / (float) PAINT_RECT_SIZE);
    int y = (int) ((float) input.mouseY * (float) FEATURES_COUNT / (float) PAINT_RECT_SIZE);

    float xF = (float) input.mouseX * (float) FEATURES_COUNT / (float) PAINT_RECT_SIZE;
    float yF = (float) input.mouseY * (float) FEATURES_COUNT / (float) PAINT_RECT_SIZE;

    if (x >= FEATURES_COUNT || y >= FEATURES_COUNT || x < 0 || y < 0) return;

    playMusic("writing");

    if (input.mouseButton == SDL_BUTTON_LEFT) {
        if (typeOfBrush == 0) {
            matrix[x][y] = 255;
            applyConvolution(matrix, x - 1, y - 1);
            applyConvolution(matrix, x, y - 1);
            applyConvolution(matrix, x - 1, y + 1);
            applyConvolution(matrix, x - 1, y);
            applyConvolution(matrix, x + 1, y);
            applyConvolution(matrix, x + 1, y - 1);
            applyConvolution(matrix, x, y + 1);
            applyConvolution(matrix, x + 1, y + 1);
        } else if (typeOfBrush == 1) {
            applyBrush(matrix, xF, yF, 2);
        }
    }
}

SDL_Rect AddButton(Button button, SDL_Renderer *renderer) {
    int imgWidth = 150;
    int imgHeight = 50;

    SDL_Surface *tmp = NULL;
    tmp = SDL_LoadBMP("../Assets/buttons/clear_btn.bmp");
    if (NULL == tmp) {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        SDL_Quit();
    }

    SDL_Rect desRect = {
            button.x,
            button.y,
            (int)((float)imgWidth * button.size),
            (int)((float)imgHeight * button.size)
    };

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tmp);
    if (NULL == texture) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        SDL_FreeSurface(tmp);
        SDL_Quit();
    }

    SDL_RenderCopy(renderer, texture, NULL, &desRect);
    SDL_FreeSurface(tmp);
    SDL_DestroyTexture(texture);
    return desRect;
}

void resetCanvas(int matrix[FEATURES_COUNT][FEATURES_COUNT]) {
    for (int x = 0; x < FEATURES_COUNT; x++) {
        for (int y = 0; y < FEATURES_COUNT; y++) {
            matrix[x][y] = 0;
        }
    }
}

void RunSdl(RandomForest *rf) {
    SDL_Window *window = initSDL();
    if (window == NULL) {
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    // Initialise la SDL2 Mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        printf("ERROR - Mix_OpenAudio %s\n", Mix_GetError());
        assert(false);
        abort();
    }
    Mix_AllocateChannels(8);

    Input input = {.quit = false};
    int matrix[FEATURES_COUNT][FEATURES_COUNT] = {0};
    Instance *predictionInstance = calloc(1, sizeof(Instance));
    AssertNew(predictionInstance);
    predictionInstance->values = (int *) calloc(FEATURES_COUNT * FEATURES_COUNT, sizeof(int));
    AssertNew(predictionInstance->values);

    // 0 = paint using sum of neighbors
    // 1 = paint using brush
    int typeOfBrush = 0;


    while (!input.quit) {
        input = getInputs();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        /*
        When u middle mouse click, it reset the matrix to black
        */
        if (input.mouseButton == SDL_BUTTON_MIDDLE) {
            resetCanvas(matrix);
        } else
            updatePaintMatrix(input, matrix, typeOfBrush);

        for (int x = 0; x < FEATURES_COUNT; x++) {
            for (int y = 0; y < FEATURES_COUNT; y++) {
                predictionInstance->values[(x * FEATURES_COUNT) + y] = matrix[x][y];
            }
        }

        int prediction = RandomForest_predict(rf, predictionInstance);

        Text settings;
        settings.x = 600;
        settings.y = 200;
        sprintf(settings.label, "%d", prediction);
        settings.color.r = 94;
        settings.color.g = 23;
        settings.color.b = 235;

        settings.fontSize = 400;
        settings.recWidth = 150;
        settings.rectHeight = 300;

        Text_New(settings, renderer);


        for (int x = 0; x < FEATURES_COUNT; x++) {
            for (int y = 0; y < FEATURES_COUNT; y++) {
                drawPainterPixel(renderer, x, y, matrix[x][y]);
            }
        }

        Button button;
        button.x = 600;
        button.y = 10;
        button.size = 1;
        SDL_Rect rect = AddButton(button, renderer);

        SDL_Point point = {input.mouseX, input.mouseY};

        if (SDL_PointInRect(&point, &rect) && input.isMouseClick) {
            resetCanvas(matrix);
        }


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}