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
    Controller(Player *player_);
    ~Controller();
    // void events();
    int test2;
    SDL_GameController *controller;

    // static int controllers;
    void registerWithEventHandler(Event &handler);
    void getMove();
    static int id;

    Event eventId1,eventId2;

    // void unregisterEvents(Event &handler);
};

#endif