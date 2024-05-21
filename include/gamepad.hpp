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
        
        void handle_events(SDL_Event const &event);												// "handle_events" method :
        void setDir(float x, float y);															// "setDir" method : 
		void connect();																			// "connect" method :
        static SDL_GameController* findController();											// "findController" method :
        static inline SDL_JoystickID getControllerInstanceID(SDL_GameController *controller);	// "getControllerInstanceID" method : 
        Controller* switchController();															// "switchController" method :

		// Public attributes

		SDL_GameController *controller;
		static int id_gamepad;

};

#endif