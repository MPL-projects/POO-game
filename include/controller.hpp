// Filename : controller.hpp

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

// Include header files
#include "utilities.hpp"

// Include libraries
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

using namespace std;

/* Definition of the class : "Controller" */

class Controller
{
	public:

		// Public Methods

		Controller();											// Constructor
		virtual ~Controller(){};								// Virtual destructor

		virtual void handle_events(SDL_Event const &event)=0;	// "handle_events" method : 
		virtual Controller* switchController()=0;				// "switchController" method : 


		// Public attributes

		std::vector<Direction> ev;

		bool att;
		bool block;
		bool changeController;
};

#endif