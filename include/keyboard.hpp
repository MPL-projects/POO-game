#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include "controller.hpp"
#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <algorithm>

using namespace std;

class Keyboard : public Controller{
    public:
        Keyboard();
        ~Keyboard();
        void getMove();
        void handle_events(SDL_Event const &event);
    private:
        // enum class Keys{UP=SDL_SCANCODE_W, DOWN=SDL_SCANCODE_S, RIGHT=SDL_SCANCODE_D, LEFT=SDL_SCANCODE_A};
        // Keys keys_g;
        void setKeys();
        std::map<std::string, vector<SDL_KeyCode>> Keys;
        int id;
        static int nb_keyboard;
        


};

#endif