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
    Player(SDL_Renderer *renderer, const char* path_to_sprite) : StickFigure(renderer, path_to_sprite) {test=5;controller = new Keyboard(this);};
    ~Player(){delete controller;};
    void handle_events(SDL_Event const &event);


    // void addController() { controller = Gamepad(); };
    // void update() { controller.events(); };
    
};
#endif