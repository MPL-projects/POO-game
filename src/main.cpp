#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include <iostream>

#include "../include/player.hpp"
#include "../include/event.hpp"
#include "../include/game.hpp"

int main(int argc, char **argv)
{
    // Player player;
    // std::cerr << player.test << std::endl;
    // player.test = 6;
    // std::cerr << player.test << std::endl;
    // player.controller->player->test = 10;
    // std::cerr << player.test << std::endl;

    // main loop
    
    Game game;

    game.run();

    return 0;
}