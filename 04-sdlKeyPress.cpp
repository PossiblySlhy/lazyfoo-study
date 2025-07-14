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
SDL_Surface* loadSurface( std::string path ); // Loads images based on the key pressed
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* currentSurface = NULL;
SDL_Surface* keyPressSurface[ KEY_PRESS_SURFACE_TOTAL ]; // Image the corresponds to the key pressed

bool init() {
    // Initialization flag
    bool success = true;

    // Initalize SDL
    if ( !SDL_Init(SDL_INIT_VIDEO) ) {
        SDL_Log( "SDL could not be initialized: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Create window
        window = SDL_CreateWindow( "SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0);

        if ( window == NULL ) {
            SDL_Log( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            screenSurface = SDL_GetWindowSurface( window );
        }
    }
}