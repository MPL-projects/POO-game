#ifndef STICKFIGURE_HPP
#define STICKFIGURE_HPP
#include <SDL2/SDL.h>
#include "spritesheet.hpp"

enum class Direction
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

class StickFigure
{
public:

    StickFigure(SDL_Renderer *renderer);
    ~StickFigure() = default;

    void handle_events(SDL_Event const &event);
    void update(double delta_time);
    void draw(SDL_Renderer *renderer);
    void move(double x1, double y1);
    double x;
    double y;
    Direction    m_direction;
    Direction    m_direction_prev;
protected:
    Spritesheet  m_spritesheet;
    int          m_spritesheet_column;
    

    SDL_Rect     m_position;
    
};
#endif