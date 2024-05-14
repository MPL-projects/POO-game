#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include <iostream>

#include "../include/player.hpp"
#include "../include/game.hpp"

int main(int argc, char **argv)
{
    Game game;

    game.run();

    return 0;
}