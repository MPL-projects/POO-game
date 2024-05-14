#include "../include/sprite.hpp"
#include "../include/window.hpp"
#include "../include/game.hpp"
#include "../include/scene.hpp"
#include <vector>
#include <map>

using namespace std;
double delta_time_ = 1.0/150.0;
int const SPRITESHEET_UP = 5;
int const SPRITESHEET_LEFT = 4;
int const SPRITESHEET_RIGHT = 4;
int const SPRITESHEET_DOWN = 3;
map<Direction, int> row_sprite = {{Direction::UP, 5}, {Direction::LEFT, 4}, {Direction::RIGHT, 4}, {Direction::DOWN, 3}};
map<Direction, vector<double>> dm = {{Direction::UP, {0, - (500.0 * delta_time_)}}, {Direction::LEFT, {- (500.0 * delta_time_), 0}}, {Direction::RIGHT, {(500.0 * delta_time_), 0}}, {Direction::DOWN, {0, (500.0 * delta_time_)}}};
map<Direction, SDL_RendererFlip> fl = {{Direction::UP, SDL_FLIP_NONE}, {Direction::LEFT, SDL_FLIP_HORIZONTAL}, {Direction::RIGHT, SDL_FLIP_NONE}, {Direction::DOWN, SDL_FLIP_NONE}};

Sprite::Sprite(SDL_Renderer *renderer, const char* path_to_sprite): m_spritesheet(path_to_sprite, 10, 6, renderer)
{
    float ratio = 2.5;
    m_position.x = 100;
    m_position.y = 100;
    m_position.w = 48 * ratio;
    m_position.h = 48 * ratio;

    x = m_position.x;
    y = m_position.y;

    bb_off.push_back({m_position.w/3, 3*m_position.h/5});
    
    // SDL_Rect r = {m_position.x + bb_off[0][0], m_position.y + bb_off[1][0], m_position.w/4, m_position.h/2};
    SDL_Rect r = {(int)x + bb_off[0][0], (int)y + bb_off[0][1], m_position.w/3, m_position.h/3};
    bb.push_back(r);
    
    
    

    m_direction = Direction::NONE;
    m_direction_prev = Direction::DOWN;

    m_spritesheet.select_sprite(0, 0);
    m_spritesheet_column = 0;

    att_dir = Direction::NONE;
    hit=false;
    block = false;
    alive = true;
}

void Sprite::update()
{
    Direction dir = att_dir;
    int mult = 10, column_int = m_spritesheet_column/mult, off=3, col = column_int;
    if(alive){
        if(block){col = 0;off = 3;dir = m_direction==Direction::NONE ? m_direction_prev : m_direction;}
        else{
            if(att_dir == Direction::NONE){
                if(m_direction == Direction::NONE){
                    dir = m_direction_prev;
                    off = -3;
                }
                else{
                    dir = m_direction;
                    move(dm[m_direction][0], dm[m_direction][1]);
                    off = 0;
                }
            }
            else{
                meleeAttack();
                if(m_spritesheet_column > mult*3){
                    att_dir = Direction::NONE;
                    bb.pop_back();
                    bb_off.pop_back();
                    hit=false;
                }
            }
        }
    }
    else{
        if(m_spritesheet_column > mult*2)
            m_spritesheet_column--;
        dir = Direction::DOWN;
        off = 6;
    }
    m_spritesheet.select_sprite(col, row_sprite[dir]+ off);
    m_spritesheet.flip = fl[dir];

    m_spritesheet_column++;

    if(m_spritesheet_column > mult*5)
        m_spritesheet_column = 0;
}

void Sprite::meleeAttack(){
    for(auto& player : Game::players){
        if(player->id != id && !hit){
            std::vector<SDL_Rect> box = player->bb;
            if(player->att_dir != Direction::NONE)
                box.pop_back();
            if(checkCollision2(bb, box)){
                hit=true;
                std::cerr << "Player " << player->id << " was hit" << std::endl;
                player->take_damage(strength);
            }
        }
    }
}

void Sprite::draw(SDL_Renderer *renderer)
{
    m_spritesheet.draw_selected_sprite(renderer, &m_position);
    // SDL_RenderDrawRect(renderer, &m_position);
    // SDL_RenderDrawRect(renderer, &bb[0]);
    // if(bb.size() > 1)
    //     SDL_RenderDrawRect(renderer, &bb.back());
}

void bounds(double &p, int bb_p, int bb_s, int bb_off_p, int size_p){
    if(bb_p < 0){p = - bb_off_p;}
    else if( bb_p + bb_s > size_p ){p = size_p - bb_s - bb_off_p;}
}

void Sprite::move(double dx, double dy){
    x += dx;
    move_boxes();

    // bool isCollisions = checkCollision(bb, Game::scene->get_boxes());
    // SDL_HasIntersection();


    // if(bb[0].x < 0){x = - bb_off[0][0];}
    // else if( bb[0].x + bb[0].w > Window::WIDTH ){x = Window::WIDTH - bb[0].w - bb_off[0][0];}
    bounds(x, bb[0].x, bb[0].w, bb_off[0][0], Game::appWindow->WIDTH);



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
    bounds(y, bb[0].y, bb[0].h, bb_off[0][1], Game::appWindow->HEIGHT);



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



void Sprite::move_boxes(){
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

std::vector<SDL_Rect>& Sprite::get_boxes()
{
    return bb;
}

void Sprite::change_skin(const char* path, SDL_Renderer *renderer){
    m_spritesheet.load_skin(path, renderer);
}