#include "../include/game.hpp"
#include "../include/player.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

bool Game::RUNNING = true;

Game::Game(){
    RUNNING = true;
    }

void Game::run(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *window = SDL_CreateWindow(
            "hello_sdl2",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

    Player player;
    player.controller->registerWithEventHandler(eventHandler);
    Player player2;
    player2.test = 6;
    player2.controller->registerWithEventHandler(eventHandler);
    while (RUNNING)
    {
        eventHandler.handleEvents();
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

}

