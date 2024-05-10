#ifndef PLAYER_HPP
#define PLAYER_HPP
//#include "sprite.hpp"
#include "gamepad.hpp"
#include <iostream>

using namespace std;

// class Player : public Sprite
class Player
{
public:
    Controller *controller = new Controller(this);
    int test;
    // Player(SDL_Renderer *renderer, const char *imagePath, int startX, int startY) : Sprite(renderer, imagePath, startX, startY){};
    // Player(const Player &player_);
    Player(){test=5; x = 0; y = 0;};
    ~Player(){delete controller;};

    // void addController() { controller = Gamepad(); };
    // void update() { controller.events(); };
    void move(float x1, float y1){x = x1; y = y1;};
    float x;
    float y;
};
#endif