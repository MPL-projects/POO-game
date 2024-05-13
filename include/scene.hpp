#ifndef SCENE_HPP
#define SCENE_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
using namespace std;

class Scene
{
public:
    Scene(){};
    virtual ~Scene(){};
    virtual void drawScene(SDL_Renderer *renderer) = 0;
    std::vector<SDL_Rect>& get_boxes(){return boxes;};

private:

    std::vector<SDL_Rect> boxes;
    
    static int id;
};

#endif