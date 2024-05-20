#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "health_bar.hpp"
#include "window.hpp"
#include "menu.hpp"
#include "scene.hpp"




#include <iostream>
#include <vector>
#include <string>

using namespace std;


//Game class

class Game
{
public:
    Game();
    ~Game();

    // void init();
    void update();
    void renderGame();
    void run();

    static bool isRunning(){return RUNNING;};
    static void stopGame(){RUNNING = false;};
    static int gameStatus;

    static vector<Player*> players;
	static vector<HealthBar *> health_bars;
    // Player *players;
    static Window *appWindow;
    Menu *mainMenu;
    Menu *mainChooseSkin1;
	Menu *mainChooseSkin2;
	Menu *endMenu;

    static Scene *scene ;
    static bool RUNNING;


private:
    void initMainMenu();
	void initEndMenu();
    void initArena();
    void drawPlayers();
	void drawHealthBars();
	void initChooseSkinPlayer1();
    void initChooseSkinPlayer2();
    void destroyGame();
};
#endif