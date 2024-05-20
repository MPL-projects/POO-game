#ifndef EFFECT_HPP
#define EFFECT_HPP
#include <SDL2/SDL.h>
#include "spritesheet.hpp"
#include "utilities.hpp"

class Effect
{
public:
    Effect(const char* path_to_effect, float ratio_, SDL_Rect position, int x_off_, int y_off_);
    ~Effect();

    void update();
    void draw();
    void move(double x1, double y1);

    double x;
    double y;
    double x_off;
    double y_off;
    bool show;

protected:
    
    Spritesheet m_spritesheet;
    int m_spritesheet_column;
    SDL_Rect m_position;

    SDL_Renderer *renderer;
    float ratio;
};
#endif