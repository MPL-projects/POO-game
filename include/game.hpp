#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "window.hpp"
#include "menu.hpp"
#include "arena.hpp"
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

    

    // Event eventHandler;
    SDL_Surface *screenSurface;
    // SDL_Window *window;

    static vector<Player*> players;
    // Player *players;
    Window *appWindow;
    Menu *mainMenu;
    static Scene *scene ;


private:
    static bool RUNNING;
    void intiMainMenu();
    void initArena();
    void drawPlayers();
    
};
#endif