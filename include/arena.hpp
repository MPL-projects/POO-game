#ifndef ARENA_HPP
#define ARENA_HPP
#include <SDL2/SDL.h>
#include "scenesheet.hpp"
#include  "scene.hpp"

class Arena : public Scene
{
public:

    Arena();
    ~Arena();

   void drawScene();
   

protected:
    int screen_width, screen_height;
    SDL_Rect     m_position;
    Scenesheet  *floor, *tree, *abandonedHouse, *water;
    SDL_Renderer *renderer;
    void drawWall();
    void drawFloor();
    void drawTree();
    void drawAbandonedHouse();
    void drawWater();
};
#endif