#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
// #include "player.hpp"
#include <SDL2/SDL.h>
// #include "event.hpp"
#include <iostream>
using namespace std;
class Player;

class Controller
{
public:
    Player *player;
    Controller(Player *player_);
    virtual ~Controller(){};

    virtual void handle_events(SDL_Event const &event)=0;
    
    static int id;
};

#endif