#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP
#include "controller.hpp"
#include <SDL2/SDL.h>

using namespace std;

class Gamepad : public Controller{
    public:
        Gamepad();
        ~Gamepad();
        SDL_GameController *controller;
        void handle_events(SDL_Event const &event);
        void setDir(float x, float y);
        static int id_gamepad;
        static SDL_GameController* findController();
        static inline SDL_JoystickID getControllerInstanceID(SDL_GameController *controller);
        void connect();
        Controller* switchController();

};

#endif