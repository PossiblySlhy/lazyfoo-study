// Using SDL to display an image
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Set screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Start SDL and create the window
bool init();

// Load media
bool loadMedia();

// Free the media and shutdown SDL
void close();

// Create the window we'll be generating the image in, including the window and surface
SDL_Window* gWindow = NULL;
SDL_Surface* gSurface = NULL;

// The image we'll display to the window
SDL_Surface* gHelloWorld = NULL;

bool init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT,0);

        if (gWindow == NULL) {
            SDL_Log("SDL_CreateWindow failed: %s\n", SDL_GetError());
            success = false;
        }
        else {
            // Get window surface
            gSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia() {
    bool success = true;

    // Load splash image
    gHelloWorld = SDL_LoadBMP("images/hello_world.bmp");
    if (!gHelloWorld) {
        SDL_Log("SDL_LoadBMP failed: %s\n", SDL_GetError());
    }

    return success;
}

void close() {
    // Deallocate surface
    SDL_DestroySurface(gHelloWorld);
    gHelloWorld = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    // Start SDL and create the window
    if (!init()) {
        SDL_Log("SDL_Init failed: %s\n", SDL_GetError());
    }
    else {
        // Load the media
        if (!loadMedia()) {
            SDL_Log("Failed to load media: %s\n", SDL_GetError());
        }
        else {
            // Apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gSurface, NULL);

            // Update surface
            SDL_UpdateWindowSurface(gWindow);

            // Temp way to fix window visibility
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_EVENT_QUIT ) quit = true; } }
        }
    }

    // Free remaining resources and close SDL
    close();

    return 0;
}