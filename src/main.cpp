#include <SDL2/SDL.h>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int TICK_SPACING = 50;
const int TICK_SIZE = 10;

void drawAxis(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Draw X axis
        SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT/2);

        // Draw Y axis
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT);
}

void drawTicks(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw ticks along the X-axis
    for (int x = 0; x <= WINDOW_WIDTH; x += TICK_SPACING) {
        SDL_RenderDrawLine(renderer, x, WINDOW_HEIGHT / 2 - TICK_SIZE / 2, x, WINDOW_HEIGHT / 2 + TICK_SIZE / 2);
    }

    // Draw ticks along the Y-axis
    for (int y = 0; y <= WINDOW_HEIGHT; y += TICK_SPACING) {
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2 - TICK_SIZE / 2, y, WINDOW_WIDTH / 2 + TICK_SIZE / 2, y);
    }
}

int main(int argc, char* argv[]){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Graphing Calculator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main Loop
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        
        drawAxis(renderer);
        drawTicks(renderer);


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    

    return 0;
}