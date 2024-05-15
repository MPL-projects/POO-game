#ifndef ARENASHEET_HPP
#define ARENASHEET_HPP
#include <SDL2/SDL.h>
#include "utilities.hpp"

class Scenesheet
{
public:
    Scenesheet(char const *path);
    ~Scenesheet();

    void select_sprite(int x, int y, int w, int h);
    void draw_selected_sprite(SDL_Rect *position);
    void set_flip(SDL_RendererFlip f){flip=f;};
    void set_rotation(int r){rotation = r;};
    
    int rotation;

private:
    
    SDL_Rect     m_clip;
    SDL_Surface *m_arena_image;
    SDL_Texture *m_arena_image_texture;
    SDL_Renderer *renderer;
    SDL_RendererFlip flip;
};
#endif