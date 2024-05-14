#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <SDL2/SDL.h>
#include "spritesheet.hpp"
#include <tuple>
#include "utilities.hpp"

class Sprite
{
public:

    Sprite(SDL_Renderer *renderer, const char* path_to_sprite);
    ~Sprite() = default;

    void handle_events(SDL_Event const &event);
    void update();
    void draw(SDL_Renderer *renderer);
    void move(double x1, double y1);

    Direction m_direction;
    Direction m_direction_prev;
    std::vector<SDL_Rect> &get_boxes();
    void move_boxes();
    void meleeAttack();
    int id;
    double x;
    double y;
    void change_skin(const char* path, SDL_Renderer *renderer);

protected:
    
    Spritesheet m_spritesheet;
    int m_spritesheet_column;
    std::vector<SDL_Rect> bb; // boundings boxes
    std::vector<std::vector<int>> bb_off; // boundings boxes offset
    SDL_Rect m_position;
    double x_off;
    double y_off;
    Direction att_dir;
    bool hit;
};
#endif