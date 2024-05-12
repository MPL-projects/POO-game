#ifndef GAME_HPP
#define GAME_HPP

#include "event.hpp"

#include <iostream>


//Game class

class Game
{
public:
    Game();
    // ~Game();

    // void init();
    // void update();
    // void render();
    void run();

    static bool isRunning(){return RUNNING;};
    static void stopGame(){RUNNING = false;};

    Event eventHandler;

private:
    static bool RUNNING;
};
#endif