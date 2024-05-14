#ifndef PLAYER_HPP
#define PLAYER_HPP
//#include "sprite.hpp"
#include "gamepad.hpp"
#include "keyboard.hpp"
#include <iostream>
#include "sprite.hpp"
#include <SDL2/SDL.h>

using namespace std;

class Player : public Sprite
{
public:
    Controller *controller;
    // Player(SDL_Renderer *renderer, const char *imagePath, int startX, int startY) : Sprite(renderer, imagePath, startX, startY){};
    // Player(const Player &player_);
    Player(SDL_Renderer *renderer, const char* path_to_sprite);
    ~Player(){delete controller;};
    void handle_events(SDL_Event const &event);

    static int nb_players;


    // void addController() { controller = Gamepad(); };
    // void update() { controller.events(); };
private:
    int strength;
    int life;
    void initMeleeAttack();
    
};
#endif