#ifndef PLAYER_HPP
#define PLAYER_HPP
//#include "sprite.hpp"
#include "gamepad.hpp"
#include "keyboard.hpp"
#include <iostream>
#include "stick_figure.hpp"
#include <SDL2/SDL.h>

using namespace std;

// class Player : public Sprite
class Player : public StickFigure
{
public:
    Controller *controller;
    int test;
    // Player(SDL_Renderer *renderer, const char *imagePath, int startX, int startY) : Sprite(renderer, imagePath, startX, startY){};
    // Player(const Player &player_);
    Player(SDL_Renderer *renderer) : StickFigure(renderer) {test=5;controller = new Keyboard();};
    ~Player(){delete controller;};
    void handle_events(SDL_Event const &event);


    // void addController() { controller = Gamepad(); };
    // void update() { controller.events(); };
    
};
#endif