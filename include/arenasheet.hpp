#ifndef ARENASHEET_HPP
#define ARENASHEET_HPP
#include <SDL2/SDL.h>
#include "utilities.hpp"

class Arenasheet
{
public:
    Arenasheet(char const *path, SDL_Renderer *renderer);
    ~Arenasheet();

    void select_sprite(int x, int y, int w, int h);
    void draw_selected_sprite(SDL_Renderer *renderervoi, SDL_Rect *position);
    void set_filp(SDL_RendererFlip f){flip=f;};
    
    SDL_RendererFlip flip;

private:
    
    SDL_Rect     m_clip;
    SDL_Surface *m_arena_image;
    SDL_Texture *m_arena_image_texture;

    
    
};
#endif