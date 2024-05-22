// Filename : effect.hpp

#ifndef EFFECT_HPP
#define EFFECT_HPP

// Include header files
#include "spritesheet.hpp"
#include "utilities.hpp"

// Include libraries
#include <SDL2/SDL.h>

/* Definition of the class : "Effect" */

class Effect
{
	public:

		// Public methods

		Effect(const char* path_to_effect, float ratio_, SDL_Rect position, int x_off_, int y_off_);	// Constructor
		~Effect();																						// Destructor

		void update();																					// "update" method : Update function to manage the effect's animation
		void draw();																					// "draw" method : Draw function to render the effect
		void move(double x1, double y1);																// "move" method : Move function to change the position of the effect


		// Public attributes

		double x;
		double y;
		double x_off;
		double y_off;

		bool show;

	protected:

		// Protected attributes 

		Spritesheet m_spritesheet;
		
		SDL_Rect m_position;
		SDL_Renderer *renderer;

		int m_spritesheet_column;

		float ratio;
};

#endif