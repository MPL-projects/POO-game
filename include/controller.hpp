#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
// #include "player.hpp"
#include <SDL2/SDL.h>
#include "event.hpp"
#include "game.hpp"
#include <iostream>
using namespace std;
class Player;

class Controller
{
public:
    Player *player;
    Controller(Player *player_);
    // ~Controller();
    // void events();

    // static int controllers;
    void registerWithEventHandler(Event &handler);
};

#endif