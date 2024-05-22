// Filename : keyboard.hpp

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

// Include header files
#include "controller.hpp"

// Include libraries
#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <algorithm>

using namespace std;


/* Definition of the class : "Keyboard" inheritating from "Controller" */

class Keyboard : public Controller
{
    public:

		// Public Methods

        Keyboard();									// Constructor
        ~Keyboard();								// Destructor

        void handle_events(SDL_Event const &event);	// "handle_events" method : Handle SDL events for the keyboard
        Controller* switchController();				// "switchController" method : Switch from keyboard to gamepad controller

    private:

		// Private attributes

        std::map<std::string, vector<SDL_KeyCode>> Keys;

        int id;

        static int nb_keyboard;
};

#endif