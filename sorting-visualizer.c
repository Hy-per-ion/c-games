#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 910
#define SCREEN_HEIGHT 750
#define ARR_SIZE 130
#define RECT_SIZE 7

int arr[ARR_SIZE];
int Barr[ARR_SIZE];

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool complete = false;

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL. SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))) {
            printf("Warning: Linear Texture Filtering not enabled.\n");
        }

        window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Couldn't create window. SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Couldn't create renderer. SDL_Error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }

    return success;
}

void close() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

void visualize(int x, int y, int z) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    int j = 0;
    for (int i = 0; i <= SCREEN_WIDTH - RECT_SIZE; i += RECT_SIZE) {
        SDL_PumpEvents();

        SDL_Rect rect = { i, 0, RECT_SIZE, arr[j] };
        if (complete) {
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderDrawRect(renderer, &rect);
        } else if (j == x || j == z) {
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderFillRect(renderer, &rect);
        } else if (j == y) {
            SDL_SetRenderDrawColor(renderer, 165, 105, 189, 0);
            SDL_RenderFillRect(renderer, &rect);
        } else {
            SDL_SetRenderDrawColor(renderer, 170, 183, 184, 0);
            SDL_RenderDrawRect(renderer, &rect);
        }
        j++;
    }
    SDL_RenderPresent(renderer);
}

void inplaceHeapSort(int* input, int n);

void randomizeAndSaveArray() {
    unsigned int seed = (unsigned)time(NULL);
    srand(seed);
    for (int i = 0; i < ARR_SIZE; i++) {
        int random = rand() % (SCREEN_HEIGHT);
        Barr[i] = random;
    }
}

void execute();

int main(int argc, char* args[]) {
    randomizeAndSaveArray();
    execute();
    return 0;
}

void execute() {
    if (!init()) {
        printf("SDL Initialization Failed.\n");
    } else {
        memcpy(arr, Barr, sizeof(int) * ARR_SIZE);

        SDL_Event e;
        bool quit = false;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0).
