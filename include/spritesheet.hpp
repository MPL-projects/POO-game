#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP
#include <SDL2/SDL.h>
#include "utilities.hpp"

class Spritesheet
{
public:
    Spritesheet(char const *path, int row, int column);
    ~Spritesheet();

    void select_sprite(int x, int y);
    void draw_selected_sprite(SDL_Renderer *renderer, SDL_Rect *position);
    SDL_RendererFlip flip;
    void load_skin(char const *path);

    SDL_Rect     m_clip;
private:
    SDL_Texture *m_spritesheet_image_texture;
    SDL_Renderer *renderer;

    int m_start_x;
    int m_start_y;

    int height;
    int width;
    int row;
    int column;
};
#endif