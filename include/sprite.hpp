// Filename : sprite.hpp

#ifndef SPRITE_HPP
#define SPRITE_HPP

// Include header files
#include "spritesheet.hpp"
#include "utilities.hpp"
#include "effect.hpp"

// Include libraries
#include <SDL2/SDL.h>


/* Definition of the class : "Sprite" */

class Sprite
{
	public:

		// Public methods

		Sprite(const char* path_to_sprite, float ratio_);	// Constructor
		~Sprite();											// Destructor

		void update();										// "update" method : 
		void draw();										// "draw" method :
		void move(double x1, double y1);					// "move" method :
		void move_boxes();									// "move_boxes" method : 
		void meleeAttack();									// "meleeAttack" method : 
		void initSprite();									// "initSprite" method :
		void change_skin(const char* path);					// "change_skin" method : 

		std::vector<SDL_Rect> &get_boxes();					// "get_boxes accessor" method : getter for boxes
		bool get_alive() {return alive;};					// "get_alive accessor" method : getter for alive
		void set_alive(bool var) {alive = var;};			// "set_alive accessor" method : setter for alive 
		void setPos(double x, double y);					// "setPos accessor" method : setter for x and y


		// Public Attributes

		Direction m_direction;
		Direction m_direction_prev;

		int id;

		double x;
		double y;

	protected:
		
		// Protected attributes

		Spritesheet m_spritesheet;

		Effect *effect;

		std::vector<SDL_Rect> bb; 							// boundings boxes
		std::vector<std::vector<int>> bb_off; 				// boundings boxes offset
		std::vector<SDL_Rect> bb_att; 						// boundings boxes
		std::vector<std::vector<int>> bb_att_off; 			// boundings boxes offset

		SDL_Rect m_position;
		SDL_Renderer *renderer;

		Direction att_dir;

		bool hit;
		bool block;
		bool alive;

		int strength;
		int m_spritesheet_column;
		
		float ratio;
};

#endif