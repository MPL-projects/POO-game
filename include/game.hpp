#ifndef GAME_HPP
#define GAME_HPP

#include "event.hpp"
#include "player.hpp"
#include "window.hpp"


#include <iostream>
#include <vector>

using namespace std;


//Game class

class Game
{
public:
    Game();
    ~Game();

    // void init();
    void update();
    void render();
    void run();

    static bool isRunning(){return RUNNING;};
    static void stopGame(){RUNNING = false;};

    

    // Event eventHandler;
    SDL_Surface *screenSurface;
    // SDL_Window *window;

    vector<Player*> players;
    // Player *players;
    Window *appWindow;


private:
    static bool RUNNING;
};
#endif