// Filename : health_bar.hpp

#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

// Include header files
#include "player.hpp"

// Include libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>


using namespace std;

/* Definition of the class : "HealthBar" */

class HealthBar 
{
	public:

		// Public methods

		HealthBar(int x, int y, int width, int height);	// Constructor
		~HealthBar();									// Destructor

		int get_x() const {return m_rect.x;};			// "get_x" accessor method : getter
		int get_y() const {return m_rect.y;};			// "get_y" accessor method : getter
		int get_w() const {return m_rect.w;};			// "get_w" accessor method : getter
		int get_h() const {return m_rect.h;};			// "get_h" accessor method : getter

		void actualDamages(int life);					// "actualDamages" method : 
		
		void render();									// "render" method : 

	private:

		// Private Attributes

		SDL_Rect m_rect;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_textTexture;

		vector<SDL_Texture*> m_textures;
		
		int m_currentTextureIndex;
		
};

#endif