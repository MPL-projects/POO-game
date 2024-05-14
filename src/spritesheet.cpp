#include "../include/spritesheet.hpp"
#include <iostream>

Spritesheet::Spritesheet(char const *path, int nb_row, int nb_column, SDL_Renderer *renderer)
{
    row = nb_row;
    column = nb_column;
    load_skin(path, renderer);
    
    flip = SDL_FLIP_NONE;
}

Spritesheet::~Spritesheet()
{
    SDL_DestroyTexture(m_spritesheet_image_texture);
}

void Spritesheet::select_sprite(int x, int y)
{
    m_clip.x = x * m_clip.w;
    m_clip.y = y * m_clip.h;
}

void Spritesheet::draw_selected_sprite(SDL_Renderer *renderer, SDL_Rect *position)
{
    
    SDL_RenderCopyEx(renderer, m_spritesheet_image_texture, &m_clip, position, 0, nullptr, flip);
    // SDL_BlitSurface(m_spritesheet_image, &m_clip, window_surface, position);
}

void Spritesheet::load_skin(char const *path, SDL_Renderer *renderer){
    m_spritesheet_image = load_bmp(path);
    m_spritesheet_image_texture = SDL_CreateTextureFromSurface(renderer, m_spritesheet_image);
    height =  m_spritesheet_image->h;
    width = m_spritesheet_image->w;
    m_clip.w = width / column;
    m_clip.h = height / row;
    SDL_FreeSurface(m_spritesheet_image);
}
