// Filename : player.hpp

#ifndef PLAYER_HPP
#define PLAYER_HPP

// Include header files
#include "gamepad.hpp"
#include "keyboard.hpp"
#include "sprite.hpp"

// Include libraries
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

/* Definition of the class : "Player" inheritating from "Sprite" */

class Player : public Sprite
{
	public:
		
		// Public methods

		Player(const char* path_to_sprite, float ratio_);	// Constructor
		~Player(){delete controller;};						// Destructor

		void handle_events(SDL_Event const &event);			// "handle_events" method : Handle events for the player
		void take_damage(int damages);						// "take_damage" method : Handle taking damage
		void initPlayer();									// "initPlayer" method : Initialize player-specific attributes

		Player operator=(const Player &player);				// "=" operator


		// Public Attributes

		int life;
		int max_life;

		Controller *controller;

		static int nb_players;

	private:

		// Private methods 

		void initMeleeAttack();								// "initMeleeAttack" method : Initialize melee attack for the player
    
};
#endif