#include "../include/window.hpp"

void Window::createWindow(const char *windowTitle, const int width, const int height){
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