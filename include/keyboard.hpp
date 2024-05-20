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
        void handle_events(SDL_Event const &event);
        Controller* switchController();
    private:
        std::map<std::string, vector<SDL_KeyCode>> Keys;
        int id;
        static int nb_keyboard;
        


};

#endif