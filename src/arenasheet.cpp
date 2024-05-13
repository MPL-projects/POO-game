#include "../include/arenasheet.hpp"
#include <iostream>

Arenasheet::Arenasheet(char const *path, SDL_Renderer *renderer)
{
    m_arena_image = load_bmp(path);
    m_arena_image_texture = SDL_CreateTextureFromSurface(renderer, m_arena_image);
    m_clip = {0,0,0,0};
   
    std::cerr << m_clip.w << " " << m_clip.h << std::endl;
    SDL_FreeSurface(m_arena_image);
    flip = SDL_FLIP_NONE;

}

Arenasheet::~Arenasheet()
{
    // SDL_FreeSurface(m_spritesheet_image);
    SDL_DestroyTexture(m_arena_image_texture);
}


void Arenasheet::select_sprite(int x, int y, int w, int h)
{
    m_clip.x = x;
    m_clip.y = y;
    m_clip.w = w;
    m_clip.h = h;
}


void Arenasheet::draw_selected_sprite(SDL_Renderer *renderer, SDL_Rect *position)
{
    // SDL_RenderCopy(renderer, m_spritesheet_image_texture, &m_clip, position);
    SDL_RenderCopyEx(renderer, m_arena_image_texture, &m_clip, position, 0, nullptr, flip);
    // SDL_BlitSurface(m_spritesheet_image, &m_clip, window_surface, position);
}




