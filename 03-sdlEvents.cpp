// Using SDL
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Establish screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Declare functions
bool init(); // Start SDL and create window
bool loadMedia(); // Loads media to the window
void close(); // Frees media and shuts down SDL

// Declare window, surface, and image to load
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Surface* xOut = NULL;

bool init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Create window
        window = SDL_CreateWindow("SDL Event Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0);

        if (window == NULL) {
            SDL_Log("SDL_CreateWindow Error: %s\n", SDL_GetError());
        }
        else {
            surface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool loadMedia() {
    // Load success flag
    bool success = true;

    // Load image
    xOut = SDL_LoadBMP("images/x.bmp");

    if (xOut == NULL) {
        SDL_Log("SDL_LoadBMP Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    // Deallocate surface
    SDL_DestroySurface(xOut);

    // Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

int main (int argc, char* args[]) {
    // Start SDL and create the window
    if (!init()) {
        SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
    }
    else {
        // Load media
        if (!loadMedia()) {
            SDL_Log("SDL_LoadBMP Error: %s\n", SDL_GetError());
        }
        else {
            // Main loop flag to check if the user has closed the application
            bool quit = false;

            // Event handler
            SDL_Event e;

            // While application is running
            while(!quit) {
                // Handle events in the queue
                while(SDL_PollEvent(&e) != 0) {
                    // User requests to quit
                    if (e.type == SDL_EVENT_QUIT) {
                        quit = true;
                    }
                }

                // Blit the image to the surface
                SDL_BlitSurface(xOut, NULL, surface, NULL);

                // Update surface
                SDL_UpdateWindowSurface(window);
            }
        }
    }

    // Free resources and close SDL
    close();
    return 0;
}