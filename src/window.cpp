#include "../include/window.hpp"
#include "../include/game.hpp"

void Window::createWindow(const char *windowTitle, const int width, const int height){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return;
    }
    WIDTH = width;
    HEIGHT = height;
    mainWindow = SDL_CreateWindow(windowTitle, 10, 10, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(mainWindow, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(mainWindow);
    mainWindow = NULL;
    SDL_Quit();   
}

void Window::handleEvents(SDL_Event &event){
    switch(event.type){
        case SDL_WINDOWEVENT:
            if(event.window.event!=SDL_WINDOWEVENT_CLOSE)
                break;
        case SDL_QUIT:
            Game::stopGame();
            break;
        // case SDL_CONTROLLERDEVICEADDED:
        //     if (!controller) {
        //         controller = SDL_GameControllerOpen(event.cdevice.which);
        //     }
        //     break;
        // case SDL_CONTROLLERDEVICEREMOVED:
        //     if (controller && event.cdevice.which == getControllerInstanceID(controller)) {
        //         SDL_GameControllerClose(controller);
        //         controller = findController();
        //     }
        //     break;
    }
}