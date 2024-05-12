#include "../include/window.hpp"
#include "../include/game.hpp"


void Window::createWindow(const char *windowTitle, const int width, const int height){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
    {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return;
    }
    mainWindow = SDL_CreateWindow(windowTitle, 10, 10, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(mainWindow, -1, 0);
    screenSurface = SDL_GetWindowSurface(mainWindow);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Window::destroyWindow(){
    SDL_UpdateWindowSurface(mainWindow);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();            
}

void Window::handleEvents(SDL_Event &event){
    if((event.type==SDL_WINDOWEVENT && event.window.event==SDL_WINDOWEVENT_CLOSE)||(event.type == SDL_QUIT) ){
        Game::stopGame();
    }
}