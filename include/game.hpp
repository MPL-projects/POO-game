#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "health_bar.hpp"
#include "window.hpp"
#include "menu.hpp"
#include "scene.hpp"
#include "utilities.hpp"
#include "soundMusic.hpp"
#include "soundEffect.hpp"




#include <iostream>
#include <vector>
#include <string>

using namespace std;


//Game class

class Game
{
public:
    ~Game();

    void run();

    static void stopGame(){RUNNING = false;};
    static GameStatus gameStatus;
    static vector<Player*> players;
	static vector<HealthBar *> health_bars;
    static Window *appWindow;
    static Scene *scene ;

    Game(Game &other) = delete;
    void operator=(const Game &) = delete;
    static Game *GetInstance(){
        if(game_==nullptr){
            game_ = new Game();
        }
        return game_;
    }

private:
    Game();
    static Game* game_;

    static bool RUNNING;
    SoundMusic *music;
    SoundEffect *soundEffect;
    Menu *mainMenu;
    Menu *mainChooseSkin1;
	Menu *mainChooseSkin2;
	Menu *endMenu;
    void update();
    void renderGame();
    void initMainMenu();
	void initEndMenu();
    void initArena();

    void drawPlayers();
	void drawHealthBars();

	void initChooseSkinPlayer1();
    void initChooseSkinPlayer2();

    void destroyGame();

	void createTransparentTexture(SDL_Texture* &texture_fin, Uint8 alpha);
	SDL_Texture *fin_texture;
    void initSound();
    void playSound();
    GameStatus save_sound;
};
#endif