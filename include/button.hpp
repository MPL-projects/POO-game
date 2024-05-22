// Filename : button.hpp

#ifndef BUTTON_HPP
#define BUTTON_HPP

// Include header files
#include "utilities.hpp"
#include "soundEffect.hpp"

// Include libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;

/* Definition of the class : "Button" */

class Button {
	public:

		// Public methods 

		Button(int x, int y, int width, int height, const vector<string>& imagePaths, const string& fontPath, const string& name, GameStatus a);	// Constructor
		~Button();																		// Destructor

		void handleEvent(const SDL_Event& event); 										// "handleEvent" method : Handle SDL events for the button
		void render();																	// "render" method : Render the button
		bool isPressed() const;															// "isPressed" method : Returns true if the button is currently pressed, false otherwise
		void setSoundEffect(SoundEffect* soundEffect, const std::string& soundId);		// "setSoundEffect" method : Sets the sound effect associated with the button

		int get_x() const {return m_rect.x;};											// get_x accessor method : getter
		int get_y() const {return m_rect.y;};											// get_x accessor method : getter
		int get_w() const {return m_rect.w;};											// get_x accessor method : getter
		int get_h() const {return m_rect.h;};											// get_x accessor method : getter


	private:

		// Private attributes

		SDL_Rect m_rect;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_textTexture;

		vector<SDL_Texture*> m_textures;

		int m_currentTextureIndex;

		TTF_Font* m_font;
		
		bool m_isPressed;

		GameStatus action;

		SoundEffect* m_soundEffect;

		std::string m_soundId;
};

#endif