#ifndef STICKFIGURE_HPP
#define STICKFIGURE_HPP
#include <SDL2/SDL.h>
#include "spritesheet.hpp"
#include <tuple>

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

    Direction m_direction;
    Direction m_direction_prev;
    std::vector<SDL_Rect> &get_boxes();
    void move_boxes();

protected:
    double x;
    double y;
    Spritesheet m_spritesheet;
    int m_spritesheet_column;
    std::vector<SDL_Rect> bb; // boundings boxes
    std::vector<std::vector<int>> bb_off; // boundings boxes offset
    SDL_Rect m_position;
    double x_off;
    double y_off;
};
#endif