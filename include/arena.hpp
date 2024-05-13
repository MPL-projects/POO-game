#ifndef ARENA_HPP
#define ARENA_HPP
#include <SDL2/SDL.h>
#include "arenasheet.hpp"

class Arena
{
public:

    Arena(SDL_Renderer *renderer, int w, int h);
    ~Arena();

    void drawArena(SDL_Renderer *renderer);

protected:
    int screen_width, screen_height;
    SDL_Rect     m_position;
    Arenasheet  *wall, *floor, *house, *tree;
    void drawWall(SDL_Renderer *renderer);
    void drawFloor(SDL_Renderer *renderer);
    void drawHouse(SDL_Renderer *renderer);
    void drawTree(SDL_Renderer *renderer);

    
    
};
#endif