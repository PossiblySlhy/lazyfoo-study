// Use SDL and standard io
#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

// Set screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {

    // Window we'll be rendering to
    SDL_Window* window = NULL;

    // Surface within the window
    SDL_Surface* screenSurface = NULL;

    // Init SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        // If successful, create Window
        window = SDL_CreateWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

        if (window == NULL) {
            SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else {
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // Fill the surface with a white color
            SDL_FillSurfaceRect(screenSurface, NULL, SDL_MapSurfaceRGB(screenSurface, 0xFF, 0xFF, 0xFF));

            // Update surface
            SDL_UpdateWindowSurface(window);

            // Temp way to keep window on the screen
            SDL_Event e; bool quit = false; while(quit == false) { while(SDL_PollEvent(&e)) { if(e.type == SDL_EVENT_QUIT) quit = true; } }
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();
    return 0;
}