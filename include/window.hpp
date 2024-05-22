// Filename : window.hpp

#ifndef WINDOW_HPP
#define WINDOW_HPP

// Include libraries
#include <SDL2/SDL.h>

/* Definition of the class : "Window" */

class Window 
{
    public:

		// Public methods

        ~Window();																		// Destructor

		void createWindow(const char *windowTitle, const int width, const int height);	// "createWindow" method : Function to create a window and initialize SDL components
        void handleEvents(SDL_Event &event);											// "handleEvents" method : Handle SDL events


		// Public attributes

        SDL_Window *mainWindow = NULL;
        SDL_Renderer *renderer = NULL;
        
        int HEIGHT;
        int WIDTH;
};

#endif