// Filename : menu.hpp

#ifndef MENU_HPP
#define MENU_HPP

// Include header files
#include "button.hpp"

// Include libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdexcept> 
#include <vector>


/* Definition of the class : "Menu" */

class Menu 
{
	public:

		// Public methods
		Menu();												// Constructor
		~Menu(); 											// Destructor to handle cleanup

		void displayMenu(bool var = true);					// "displayMenu" method : Display the menu, optionally rendering the background
		void handleEvents(SDL_Event &event);				// "handleEvents" method : Handle events for the menu
		void addButton(Button* button); 					// "addButton" method : Add a button to the menu
		bool buttonStatus(Button* button);					// "buttonStatus" method : Check if a button is pressed

		void setBackground(const std::string&  imagePath);	// "setBackGround" acessor method : setter
		SDL_Texture* getBackground(){return back_texture;};	// "getBackground" accessor method : getter


		// Public attributes

		SDL_Renderer *m_renderer;

	private:

		// Private methods
		void render_background();							// "render_background" method : Render the background texture


		//Private attributes

		std::vector<Button*> buttons;

		SDL_Texture *back_texture;

		int windowHeight, windowWidth;

		
};

#endif
