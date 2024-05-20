#ifndef SCENE_HPP
#define SCENE_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "utilities.hpp"

using namespace std;

class Scene
{
public:
    Scene(){};
    virtual ~Scene(){};
    void drawScene();
    void draw_boxes();
    std::vector<SDL_Rect>& get_boxes(){return boxes;};

    void load_scene(const std::string& jsonFilePath);
    Param set_param(SDL_Rect pos, SDL_RendererFlip flip, int rotation);
    Clip set_clip(SDL_Rect clip, vector<Param> params);
    Tiles set_tiles(SDL_Texture *asset, std::vector<Clip> clips);

private:

    std::vector<SDL_Rect> boxes;
    vector<Tiles> assests;
    
    static int id;
};

#endif