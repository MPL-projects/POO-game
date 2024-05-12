#ifndef STICKFIGURE_HPP
#define STICKFIGURE_HPP
#include <SDL2/SDL.h>
#include "spritesheet.hpp"

class StickFigure
{
public:
    enum class Direction
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    StickFigure(SDL_Renderer *renderer);
    ~StickFigure() = default;

    void handle_events(SDL_Event const &event);
    void update(double delta_time);
    void draw(SDL_Renderer *renderer);
    double       x;
    double       y;
protected:
    Spritesheet  m_spritesheet;
    int          m_spritesheet_column;
    Direction    m_direction;
    Direction    m_direction_prev;

    SDL_Rect     m_position;
    
};
#endif