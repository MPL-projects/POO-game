#include "../include/stick_figure.hpp"
#include "../include/window.hpp"
#include "../include/game.hpp"

int const SPRITESHEET_UP = 5;
int const SPRITESHEET_LEFT = 4;
int const SPRITESHEET_RIGHT = 4;
int const SPRITESHEET_DOWN = 3;

StickFigure::StickFigure(SDL_Renderer *renderer): m_spritesheet("assets/images/players/player1.png", 10, 6, renderer)
{
    float ratio = 2.5;
    m_position.x = 0;
    m_position.y = 0;
    m_position.w = 48 * ratio;
    m_position.h = 48 * ratio;

    x = 0.0;
    y = 0.0;

    m_direction = Direction::NONE;
    m_direction_prev = Direction::DOWN;

    m_spritesheet.select_sprite(0, 0);
    m_spritesheet_column = 0;
}

void StickFigure::update(double delta_time)
{
    m_spritesheet.flip = SDL_FLIP_NONE;
    switch(m_direction)
    {
        case Direction::NONE:
            switch(m_direction_prev)
                {
                    case Direction::NONE:
                    break;
                    case Direction::UP:
                        m_spritesheet.select_sprite(m_spritesheet_column, SPRITESHEET_UP-3);
                        break;
                    case Direction::DOWN:
                        m_spritesheet.select_sprite(m_spritesheet_column, SPRITESHEET_DOWN-3);
                        break;
                    case Direction::LEFT:
                        m_spritesheet.select_sprite(m_spritesheet_column, SPRITESHEET_LEFT-3);
                        m_spritesheet.flip = SDL_FLIP_HORIZONTAL;
                        break;
                    case Direction::RIGHT:
                        m_spritesheet.select_sprite(m_spritesheet_column, SPRITESHEET_RIGHT-3);
                        break;
                }
            break;
        case Direction::UP:
            move(0, - (500.0 * delta_time));
            m_spritesheet.select_sprite(m_spritesheet_column, SPRITESHEET_UP);
            break;
        case Direction::DOWN:
            move(0, (500.0 * delta_time));
            m_spritesheet.select_sprite(m_spritesheet_column, SPRITESHEET_DOWN);
            break;
        case Direction::LEFT:
            move(- (500.0 * delta_time), 0);
            m_spritesheet.select_sprite(m_spritesheet_column, SPRITESHEET_LEFT);
            m_spritesheet.flip = SDL_FLIP_HORIZONTAL;
            break;
        case Direction::RIGHT:
            move((500.0 * delta_time), 0);
            m_spritesheet.select_sprite(m_spritesheet_column, SPRITESHEET_RIGHT);
            break;
    }

    m_spritesheet_column++;

    if(m_spritesheet_column > 5)
        m_spritesheet_column = 0;
}

void StickFigure::draw(SDL_Renderer *renderer)
{
    m_spritesheet.draw_selected_sprite(renderer, &m_position);
}

void StickFigure::move(double dx, double dy){
    x += dx;
    y += dy;
    move_boxes(dx, dy);

    bool isCollisions = checkCollision(collisions_boxes, otherColliders);

    if( ( x < 0 ) || ( x + m_position.w > Window::WIDTH ) || isCollisions )
    {
        //Move back
        x -= dx;
        move_boxes(-dx,0);
    }

    //If the dot collided or went too far up or down
    if( ( y < 0 ) || ( y + m_position.h > Window::HEIGHT ) || isCollisions )
    {
        //Move back
        y -= dy;
        move_boxes(0,-dy);
    }

    m_position.x = x;
    m_position.y = y;
    
}

void StickFigure::move_boxes(double dx, double dy){
    //Go through the dot's collision boxes
    for(auto &box : collisions_boxes)
    {
        box.x += dx;
        box.y += dy;
    }
}

std::vector<SDL_Rect> StickFigure::get_boxes()
{
    return collisions_boxes;
}