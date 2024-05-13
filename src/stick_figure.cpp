#include "../include/stick_figure.hpp"
#include "../include/window.hpp"
#include "../include/game.hpp"
#include "../include/scene.hpp"
#include <vector>

int const SPRITESHEET_UP = 5;
int const SPRITESHEET_LEFT = 4;
int const SPRITESHEET_RIGHT = 4;
int const SPRITESHEET_DOWN = 3;

StickFigure::StickFigure(SDL_Renderer *renderer, const char* path_to_sprite): m_spritesheet(path_to_sprite, 10, 6, renderer)
{
    float ratio = 2.5;
    m_position.x = 100;
    m_position.y = 100;
    m_position.w = 48 * ratio;
    m_position.h = 48 * ratio;

    x = m_position.x;
    y = m_position.y;

    bb_off.push_back({m_position.w/3, 2*m_position.h/5});
    
    // SDL_Rect r = {m_position.x + bb_off[0][0], m_position.y + bb_off[1][0], m_position.w/4, m_position.h/2};
    SDL_Rect r = {(int)x + bb_off[0][0], (int)y + bb_off[0][1], m_position.w/3, m_position.h/2};
    bb.push_back(r);
    
    
    

    m_direction = Direction::NONE;
    m_direction_prev = Direction::DOWN;

    m_spritesheet.select_sprite(0, 0);
    m_spritesheet_column = 0;

    att_dir = Direction::NONE;
    hit=false;
}

void StickFigure::update(double delta_time)
{
    m_spritesheet.flip = SDL_FLIP_NONE;
    int mult = 2;
    int column_int = m_spritesheet_column/mult;
    if(att_dir == Direction::NONE){
        switch(m_direction)
        {
            case Direction::NONE:
                switch(m_direction_prev)
                    {
                        case Direction::NONE:
                        break;
                        case Direction::UP:
                            m_spritesheet.select_sprite(column_int, SPRITESHEET_UP-3);
                            break;
                        case Direction::DOWN:
                            m_spritesheet.select_sprite(column_int, SPRITESHEET_DOWN-3);
                            break;
                        case Direction::LEFT:
                            m_spritesheet.select_sprite(column_int, SPRITESHEET_LEFT-3);
                            m_spritesheet.flip = SDL_FLIP_HORIZONTAL;
                            break;
                        case Direction::RIGHT:
                            m_spritesheet.select_sprite(column_int, SPRITESHEET_RIGHT-3);
                            break;
                    }
                break;
            case Direction::UP:
                move(0, - (500.0 * delta_time));
                m_spritesheet.select_sprite(column_int, SPRITESHEET_UP);
                break;
            case Direction::DOWN:
                move(0, (500.0 * delta_time));
                m_spritesheet.select_sprite(column_int, SPRITESHEET_DOWN);
                break;
            case Direction::LEFT:
                move(- (500.0 * delta_time), 0);
                m_spritesheet.select_sprite(column_int, SPRITESHEET_LEFT);
                m_spritesheet.flip = SDL_FLIP_HORIZONTAL;
                break;
            case Direction::RIGHT:
                move((500.0 * delta_time), 0);
                m_spritesheet.select_sprite(column_int, SPRITESHEET_RIGHT);
                break;
        }
    }
    else{
        switch(att_dir)
        {
            case Direction::NONE:
            break;
            case Direction::UP:
                m_spritesheet.select_sprite(column_int, SPRITESHEET_UP+3);
                break;
            case Direction::DOWN:
                m_spritesheet.select_sprite(column_int, SPRITESHEET_DOWN+3);
                break;
            case Direction::LEFT:
                m_spritesheet.select_sprite(column_int, SPRITESHEET_LEFT+3);
                m_spritesheet.flip = SDL_FLIP_HORIZONTAL;
                break;
            case Direction::RIGHT:
                m_spritesheet.select_sprite(column_int, SPRITESHEET_RIGHT+3);
                break;
        }
        meleeAttack();
        if(m_spritesheet_column > mult*3){
            att_dir = Direction::NONE;
            bb.pop_back();
            bb_off.pop_back();
            hit=false;
        }
    }

    m_spritesheet_column++;

    if(m_spritesheet_column > mult*5)
        m_spritesheet_column = 0;
}

void StickFigure::meleeAttack(){
    for(auto& player : Game::players){
        if(player->id != id && !hit){
            if(checkCollision2(bb, player->bb)){
                hit=true;
                std::cerr << "Player " << player->id << " was hit" << std::endl;
            }
        }
    }
}

void StickFigure::draw(SDL_Renderer *renderer)
{
    m_spritesheet.draw_selected_sprite(renderer, &m_position);
    // SDL_RenderDrawRect(renderer, &m_position);
    SDL_RenderDrawRect(renderer, &bb[0]);
    if(bb.size() > 1)
        SDL_RenderDrawRect(renderer, &bb.back());
}

void bounds(double &p, int bb_p, int bb_s, int bb_off_p, int size_p){
    if(bb_p < 0){p = - bb_off_p;}
    else if( bb_p + bb_s > size_p ){p = size_p - bb_s - bb_off_p;}
}

void StickFigure::move(double dx, double dy){
    x += dx;
    move_boxes();

    // bool isCollisions = checkCollision(bb, Game::scene->get_boxes());
    // SDL_HasIntersection();


    // if(bb[0].x < 0){x = - bb_off[0][0];}
    // else if( bb[0].x + bb[0].w > Window::WIDTH ){x = Window::WIDTH - bb[0].w - bb_off[0][0];}
    bounds(x, bb[0].x, bb[0].w, bb_off[0][0], Window::WIDTH);



    // if( ( bb[0].x < 0 ) || ( bb[0].x + bb[0].w > Window::WIDTH ) || isCollisions )
    // {
    //     //Move back
    //     x -= dx;
    //     move_boxes();
    // }
    move_boxes(); // not necessary

    y += dy;
    move_boxes();
    // isCollisions = checkCollision(bb, Game::scene->get_boxes());


    // if(bb[0].y < 0){y = - bb_off[0][1];}
    // else if( bb[0].y + bb[0].h > Window::HEIGHT ){y = Window::HEIGHT - bb[0].h - bb_off[0][1];}
    bounds(y, bb[0].y, bb[0].h, bb_off[0][1], Window::HEIGHT);



    //If the dot collided or went too far up or down
    // if( ( bb[0].y < 0 ) || ( bb[0].y + bb[0].h > Window::HEIGHT ) || isCollisions )
    // {
    //     //Move back
    //     y -= dy;
    //     move_boxes();
    // }
    move_boxes();

    m_position.x = x;
    m_position.y = y;
    
}



void StickFigure::move_boxes(){
    for( int i = 0; i < (int)bb.size(); i++ )
    {
        bb[i].x = x + bb_off[i][0];
        bb[i].y = y + bb_off[i][1];
    }
    // //Go through the dot's collision boxes
    // for(auto &box : collisions_boxes)
    // {
    //     box.x += dx;
    //     box.y += dy;
    // }
    //The row offset
    // int r = 0;

    // //Go through the dot's collision boxes
    // for( int set = 0; set < mColliders.size(); ++set )
    // {
    //     //Center the collision box
    //     mColliders[ set ].x = mPosX + ( DOT_WIDTH - mColliders[ set ].w ) / 2;

    //     //Set the collision box at its row offset
    //     mColliders[ set ].y = mPosY + r;

    //     //Move the row offset down the height of the collision box
    //     r += mColliders[ set ].h;
    // }
}

std::vector<SDL_Rect>& StickFigure::get_boxes()
{
    return bb;
}