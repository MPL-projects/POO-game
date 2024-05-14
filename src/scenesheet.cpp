#include "../include/scenesheet.hpp"
#include "../include/game.hpp"
#include <iostream>

Scenesheet::Scenesheet(char const *path) : renderer(Game::appWindow->renderer)
{
    m_arena_image = load_png(path);
    m_arena_image_texture = SDL_CreateTextureFromSurface(renderer, m_arena_image);
    m_clip = {0,0,0,0};
   
    // std::cerr << m_clip.w << " " << m_clip.h << std::endl;
    SDL_FreeSurface(m_arena_image);
    flip = SDL_FLIP_NONE;
    rotation = 0;

}

Scenesheet::~Scenesheet()
{
    // SDL_FreeSurface(m_spritesheet_image);
    SDL_DestroyTexture(m_arena_image_texture);
}


void Scenesheet::select_sprite(int x, int y, int w, int h)
{
    m_clip.x = x;
    m_clip.y = y;
    m_clip.w = w;
    m_clip.h = h;
}


void Scenesheet::draw_selected_sprite(SDL_Rect *position)
{
    // SDL_RenderCopy(renderer, m_spritesheet_image_texture, &m_clip, position);
    SDL_RenderCopyEx(renderer, m_arena_image_texture, &m_clip, position, rotation, nullptr, flip);
    // SDL_BlitSurface(m_spritesheet_image, &m_clip, window_surface, position);
}





