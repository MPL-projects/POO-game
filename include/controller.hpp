#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
// #include "player.hpp"
#include <SDL2/SDL.h>
// #include "event.hpp"
#include <iostream>
#include <vector>
#include "utilities.hpp"
using namespace std;

class Controller
{
public:
    Controller();
    virtual ~Controller(){};

    virtual void handle_events(SDL_Event const &event)=0;
    
    static int id;

    std::vector<Direction> ev;
};

#endif