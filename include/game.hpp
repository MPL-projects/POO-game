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

		void run();									// "run" method : Run the game loop
		static void stopGame(){RUNNING = false;};	// "stopGame" method : Stop game loop
		Game(Game &other) = delete;					// "..." method
		void operator=(const Game &) = delete;		// "=" operator method
		static Game *GetInstance(){					// "GetInstance" Method
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

		void update();					// "update" method : Update game state
		void renderGame();				// "renderGame" method : Render game elements
		void initMainMenu();			// "initMainMenu" method : Initialize the main menu
		void initEndMenu();				// "initEndMenu" method : Initialize the end menu
		void initArena();				// "initArena" method : 

		void drawPlayers();				// "drawPlayers" method : Draw players
		void drawHealthBars();			// "drawHealthBars" method : Draw health bars

		void initChooseSkinPlayer1();	// "initChooseSkinPlayer1" method : Initialize the menu to choose the skin for player 1
		void initChooseSkinPlayer2();	// "initChooseSkinPlayer2" method : Initialize the menu to choose the skin for player 2

		void destroyGame();				// "destroyGame" method : Destroy game resources

		void initSound();				// "initSound" method : Initialize game sounds
		void playSound();				// "PlaySound" method : Play background music and sound effects

		void createTransparentTexture(SDL_Texture* &texture_fin, Uint8 alpha);	// "createTransparentTexture" method : Create a transparent texture


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