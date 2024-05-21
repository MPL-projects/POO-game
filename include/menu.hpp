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

		void displayMenu(bool var = true);					// "displayMenu" method : 
		void handleEvents(SDL_Event &event);				// "handleEvents" method : 
		void addButton(Button* button); 					// "addButton" method : to add buttons to the menu
		bool buttonStatus(Button* button);					// "buttonStatus" method : 

		void setBackground(const std::string&  imagePath);	// "setBackGround" acessor method : setter
		SDL_Texture* getBackground(){return back_texture;};	// "getBackground" accessor method : getter


		// Public attributes

		SDL_Renderer *m_renderer;

	private:

		// Private methods
		void render_background();							// "render_background" method :


		//Private attributes

		std::vector<Button*> buttons;

		SDL_Texture *back_texture;

		int windowHeight, windowWidth;

		
};

#endif
