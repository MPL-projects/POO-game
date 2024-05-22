// Filename : spritesheet.hpp

#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

// Include libraries
#include <SDL2/SDL.h>
#include "utilities.hpp"

/* Definition of the class : "SpriteSheet" */

class Spritesheet
{
	public:

		// Public methods 

		Spritesheet(char const *path, int row, int column);						// Constructor
		~Spritesheet();															// Destructor

		void select_sprite(int x, int y);										// "select_sprite" method : Select a specific sprite from the spritesheet
		void draw_selected_sprite(SDL_Renderer *renderer, SDL_Rect *position);	// "draw_selected_sprite" method : Draw the selected sprite on the screen
		void load_skin(char const *path);										// "load_skin" method : Load the spritesheet image from a file


		// Public attributes

		SDL_RendererFlip flip;
		SDL_Rect     m_clip;

	private:

		// Private attributes

		SDL_Texture *m_spritesheet_image_texture;
		SDL_Renderer *renderer;

		int m_start_x;
		int m_start_y;

		int height;
		int width;
		int row;
		int column;
};

#endif