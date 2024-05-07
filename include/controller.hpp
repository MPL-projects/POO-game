#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
// #include "player.hpp"
#include <SDL2/SDL.h>
#include "event.hpp"
#include <iostream>
using namespace std;
class Player;

class Controller
{
public:
    Player *player;
    Controller(Player *player_)
    {
        player = player_;
    }
    // ~Controller();
    // void events();

    // static int controllers;
    void registerWithEventHandler(Event &handler)
    {
        handler.registerEvent(SDL_KEYUP, [this](SDL_Event const &event){
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                std::cerr << "test1" << std::endl;
                } 
            });
        handler.registerEvent(SDL_QUIT, [this](SDL_Event const &event){
            std::cerr << "test2" << std::endl; 
            });
    }
};

#endif