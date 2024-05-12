#ifndef PLAYER_HPP
#define PLAYER_HPP
//#include "sprite.hpp"
#include "gamepad.hpp"
#include <iostream>
#include "stick_figure.hpp"
#include <SDL2/SDL.h>

using namespace std;

// class Player : public Sprite
class Player : public StickFigure
{
public:
    Controller *controller = new Controller(this);
    int test;
    // Player(SDL_Renderer *renderer, const char *imagePath, int startX, int startY) : Sprite(renderer, imagePath, startX, startY){};
    // Player(const Player &player_);
<<<<<<< HEAD
    Player(SDL_Renderer *renderer) : StickFigure(renderer) {test=5;};
    ~Player(){delete controller;};
=======
    Player(){test=5; x = 0; y = 0;};
<<<<<<< HEAD
    ~Player(){delete controller;};
=======
    ~Player(){
        delete controller;
        };
>>>>>>> main
>>>>>>> 20192e9d467df85be1faa52dc84e3d4a3c8af13c

    // void addController() { controller = Gamepad(); };
    // void update() { controller.events(); };
    void move(double x1, double y1){m_x = x1; m_y = y1;};
};
#endif