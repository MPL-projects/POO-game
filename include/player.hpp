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
    Player(SDL_Renderer *renderer) : StickFigure(renderer) {test=5;};
    ~Player(){delete controller;};

    // void addController() { controller = Gamepad(); };
    // void update() { controller.events(); };
    void move(double x1, double y1){m_x = x1; m_y = y1;};
};
#endif