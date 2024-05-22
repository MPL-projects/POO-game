// Filename : gamepad.hpp

#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP

// Include header files
#include "controller.hpp"

// Include libraries
#include <SDL2/SDL.h>

using namespace std;

/* Definition of the class : "Gamepad" inheritating from "Controller" */

class Gamepad : public Controller
{
    public:

		// Public methods

        Gamepad();																				// Constructor
        ~Gamepad();																				// Destructor
        
        void handle_events(SDL_Event const &event);												// "handle_events" method : Handle SDL events for the gamepad
        void setDir(float x, float y);															// "setDir" method : Set the direction based on joystick input
		void connect();																			// "connect" method : Connect the gamepad
        static SDL_GameController* findController();											// "findController" method : Find and open a gamepad controller
        static inline SDL_JoystickID getControllerInstanceID(SDL_GameController *controller);	// "getControllerInstanceID" method : Get the instance ID of the gamepad controller
        Controller* switchController();															// "switchController" method : Switch to keyboard controller

		// Public attributes

		SDL_GameController *controller;
		static int id_gamepad;

};

#endif