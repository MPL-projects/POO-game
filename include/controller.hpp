#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SDL2/SDL.h>
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
    virtual Controller* switchController()=0;

    std::vector<Direction> ev;
    bool att;
    bool block;
    bool changeController;
};

#endif