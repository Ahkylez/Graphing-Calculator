#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
    
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

float scale = 50;
float offsetX = WINDOW_WIDTH/2;
float offsetY = WINDOW_HEIGHT/2;

void drawGrid(SDL_Renderer* renderer, int width, int height, float scale, float offsetX, float offsetY){
    
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
    // Draw x lines (Vertical)
    for (int x = -offsetX; x < width; x += scale){
        // clean up this logic later
        // if (x % 8 == 0){
        //     SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        //     SDL_RenderDrawLine(renderer, x + offsetX, 0, x + offsetX, height);
        //     SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
        // }
        // else {
        //     SDL_RenderDrawLine(renderer, x + offsetX, 0, x + offsetX, height);
        // }
        SDL_RenderDrawLine(renderer, x + offsetX, 0, x + offsetX, height);
        
    }

    // Draw y lines (horizontal)
    for (int y = -offsetY; y < height; y += scale){
        // if (y % 8 == 0){
        //     SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        //     SDL_RenderDrawLine(renderer, 0, y + offsetY, width, y + offsetY);
        //     SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
        // }
        // else {
        //     SDL_RenderDrawLine(renderer, 0, y + offsetY, width, y + offsetY);
        // }
        SDL_RenderDrawLine(renderer, 0, y + offsetY, width, y + offsetY);
    }

    // Draw x-axis
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 0, offsetY, width, offsetY);

    // Draw y-axis
    SDL_RenderDrawLine(renderer, offsetX, 0, offsetX, height);
}

void handleInput(SDL_Event& event, float& scale, float& offsetX, float& offsetY) {
    if (event.type == SDL_MOUSEWHEEL) {
        if (event.wheel.y > 0) { // Zoom in
            scale *= 1.1f;
        } else if (event.wheel.y < 0) { // Zoom out
            scale *= 0.9f;
        }
    } else if (event.type == SDL_MOUSEMOTION && (event.motion.state & SDL_BUTTON_LMASK)) {
        offsetX += event.motion.xrel;
        offsetY += event.motion.yrel;
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
            handleInput(event, scale, offsetX, offsetY);
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawGrid(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, scale, offsetX, offsetY);
        
        SDL_RenderPresent(renderer);
    }




    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    

    return 0;
}