#include "../include/window.hpp"
#include "../include/game.hpp"

// Function to create a window and initialize SDL components
void Window::createWindow(const char *windowTitle, const int width, const int height) {
    // Initialize SDL video, game controller, and audio subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());  // Print an error message if initialization fails
        return;
    }

    // Initialize SDL_mixer for audio playback
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;  // Print an error message if audio initialization fails
        return;
    }

    // Set window dimensions
    WIDTH = width;
    HEIGHT = height;

    // Create the main SDL window
    mainWindow = SDL_CreateWindow(windowTitle, 10, 10, width, height, SDL_WINDOW_SHOWN);
    
    // Create the renderer for the window
    renderer = SDL_CreateRenderer(mainWindow, -1, 0);

    // Set the default draw color for the renderer to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

// Destructor for the Window class
Window::~Window() {
    SDL_DestroyRenderer(renderer);  // Destroy the renderer
    renderer = NULL;  // Set the renderer pointer to NULL
    SDL_DestroyWindow(mainWindow);  // Destroy the main window
    mainWindow = NULL;  // Set the main window pointer to NULL
    Mix_CloseAudio();  // Close the SDL_mixer audio
    SDL_Quit();  // Quit SDL subsystems
}

// Handle SDL events
void Window::handleEvents(SDL_Event &event) {
    switch(event.type) {
        // Handle window events
        case SDL_WINDOWEVENT:
            if (event.window.event != SDL_WINDOWEVENT_CLOSE)  // If the window event is not close
                break;

        // Handle quit event
        case SDL_QUIT:
            Game::stopGame();  // Stop the game if quit event occurs
            break;

        // Handle controller device added event (commented out)
        // case SDL_CONTROLLERDEVICEADDED:
        //     if (!controller) {
        //         controller = SDL_GameControllerOpen(event.cdevice.which);
        //     }
        //     break;

        // Handle controller device removed event (commented out)
        // case SDL_CONTROLLERDEVICEREMOVED:
        //     if (controller && event.cdevice.which == getControllerInstanceID(controller)) {
        //         SDL_GameControllerClose(controller);
        //         controller = findController();
        //     }
        //     break;
    }
}
