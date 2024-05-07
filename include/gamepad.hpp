#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP
#include "controller.hpp"
#include <SDL2/SDL.h>

using namespace std;

class Gamepad : public Controller{
    public:
        Gamepad();
        SDL_GameController *findGamepad();

};

#endif