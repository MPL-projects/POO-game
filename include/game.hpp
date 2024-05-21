// Filename : game.hpp

#ifndef GAME_HPP
#define GAME_HPP

// Include header files
#include "player.hpp"
#include "health_bar.hpp"
#include "window.hpp"
#include "menu.hpp"
#include "scene.hpp"
#include "utilities.hpp"
#include "soundMusic.hpp"
#include "soundEffect.hpp"

// Include libraries
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* Definition of the class : "Game" */

class Game
{
	public:

		// Public Methods

		~Game();									// Destructor

		void run();									// "run" method : 
		static void stopGame(){RUNNING = false;};	// "stopGame" method : 
		Game(Game &other) = delete;					// "..." method :
		void operator=(const Game &) = delete;		// "=" operator method : 
		static Game *GetInstance(){					// "GetInstance" Method : 
			if(game_==nullptr){
				game_ = new Game();
			}
			return game_;
		}


		// Public Attributes 

		static GameStatus gameStatus;

		static vector<Player*> players;
		static vector<HealthBar *> health_bars;

		static Window *appWindow;

		static Scene *scene ;

		
		

	private:

		// Private Methods

		Game();							// Constructor

		void update();					// "update" method : 
		void renderGame();				// "renderGame" method : 
		void initMainMenu();			// "initMainMenu" method : 
		void initEndMenu();				// "initEndMenu" method : 
		void initArena();				// "initArena" method : 

		void drawPlayers();				// "drawPlayers" method : 
		void drawHealthBars();			// "drawHealthBars" method : 

		void initChooseSkinPlayer1();	// "initChooseSkinPlayer1" method : 
		void initChooseSkinPlayer2();	// "initChooseSkinPlayer2" method : 

		void destroyGame();				// "destroyGame" method : 

		void initSound();				// "initSound" method : 
		void playSound();				// "PlaySound" method : 

		void createTransparentTexture(SDL_Texture* &texture_fin, Uint8 alpha);	// "createTransparentTexture" method : 


		// Private attributes

		static Game* game_;

		static bool RUNNING;

		SoundMusic *music;
		SoundEffect *soundEffect;

		Menu *mainMenu;
		Menu *mainChooseSkin1;
		Menu *mainChooseSkin2;
		Menu *endMenu;

		SDL_Texture *fin_texture;

		GameStatus save_sound;
};

#endif