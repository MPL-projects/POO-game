#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include <iostream>

#include "../include/player.hpp"
#include "../include/game.hpp"

// int main(int argc, char **argv)
// {
//     Game game;
//     game.run();
//     return 0;
// }
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../include/soundMusic.hpp"

SoundMusic* musicManager;

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cerr << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

void closeSDL() {
    Mix_CloseAudio();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!initSDL()) {
        return -1;
    }

    musicManager = new SoundMusic();
    musicManager->loadSound("soundA", "assets/musics/themes/desperate_battle.ogg");
    musicManager->loadSound("soundB", "assets/Sounds/Game/sound1.ogg");

    SDL_Window* window = SDL_CreateWindow("Sound Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_a:
                        musicManager->playSound("soundA");
                        break;
                    case SDLK_b:
                        musicManager->playSound("soundB");
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    musicManager->cleanSound();
    delete musicManager;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    closeSDL();
    return 0;
}