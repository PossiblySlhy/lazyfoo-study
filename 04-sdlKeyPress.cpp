// Using SDL3 and strings
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

// Establish screen constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Establish key press surface constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_TOTAL
};

// Declare functions
bool init(); // Starts SDL and creates the window
bool loadMedia(); // Loads media to be displayed
void close(); // Frees media and shuts down SDL

// Establish SDL pointers
SDL_Surface* loadSurface(std::string path); // Loads images based on the key pressed
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* currentSurface = NULL;
SDL_Surface* keyPressSurface[KEY_PRESS_SURFACE_TOTAL]; // Image the corresponds to the key pressed

bool init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not be initialized: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Create window
        window = SDL_CreateWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0);

        if (window == NULL) {
            SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool loadMedia() {
    // Load success flag
    bool success = true;

    // Load default surface
    keyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/press.bmp");
    if (keyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        SDL_Log("Failed to load default image: SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    // Load up surface
    keyPressSurface[KEY_PRESS_SURFACE_UP] = loadSurface("images/up.bmp");
    if (keyPressSurface[KEY_PRESS_SURFACE_UP] == NULL) {
        SDL_Log("Failed to load up image: SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    // Load down surface
    keyPressSurface[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/down.bmp");
    if (keyPressSurface[KEY_PRESS_SURFACE_DOWN] == NULL) {
        SDL_Log("Failed to load down image: SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    // Load right surface
    keyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/right.bmp");
    if (keyPressSurface[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        SDL_Log("Failed to load right image: SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    // Load left surface
    keyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/left.bmp");
    if (keyPressSurface[KEY_PRESS_SURFACE_LEFT] == NULL) {
        SDL_Log("Failed to load left image: SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    // Deallocate surfaces
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        SDL_DestroySurface(keyPressSurface[i]);
        keyPressSurface[i] = NULL;
    }

    // Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {
    // Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        SDL_Log("Failed to load image: %s\n", SDL_GetError());
    }

    return loadedSurface;
}

int main(int argc, char* args[]) {
    // Start SDL and create window
    if (!init()) {
        SDL_Log("Failed to initialize!\n");
    }
    else {
        // Main loop flag
        bool quit = false;

        // Event handler
        SDL_Event e;

        // Set default current surface
        currentSurface = keyPressSurface[KEY_PRESS_SURFACE_DEFAULT];

        // While application is running
        while(!quit) {
            // Handle events in the queue
            while(SDL_PollEvent(&e) != 0) {
                // User requests to quit
                if (e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
                // User presses a key
                else if (e.type == SDL_EVENT_KEY_DOWN) {
                    switch (e.key.key) {
                        case SDLK_UP:
                            currentSurface = keyPressSurface[KEY_PRESS_SURFACE_UP];
                            break;
                        case SDLK_DOWN:
                            currentSurface = keyPressSurface[KEY_PRESS_SURFACE_DOWN];
                            break;
                        case SDLK_RIGHT:
                            currentSurface = keyPressSurface[KEY_PRESS_SURFACE_RIGHT];
                            break;
                        case SDLK_LEFT:
                            currentSurface = keyPressSurface[KEY_PRESS_SURFACE_LEFT];
                            break;

                        default:
                            currentSurface = keyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                    }
                }
            }

            // Apply the current image and update
            SDL_BlitSurface(currentSurface, NULL, screenSurface, NULL);
            SDL_UpdateWindowSurface(window);
        }
    }

    // Free resources and close SDL
    close();
    return 0;
}