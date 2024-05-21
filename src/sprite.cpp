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

Sprite::Sprite(const char* path_to_sprite, float ratio_): m_spritesheet(path_to_sprite, 10, 6), ratio(ratio_)
{
    
    renderer = Game::appWindow->renderer;
    m_position.x = 0;
    m_position.y = 0;
    m_position.w = 48 * ratio;
    m_position.h = 48 * ratio;

    x = m_position.x;
    y = m_position.y;

    bb_off.push_back({m_position.w/3, 3*m_position.h/5});
    
    // SDL_Rect r = {m_position.x + bb_off[0][0], m_position.y + bb_off[1][0], m_position.w/4, m_position.h/2};
    SDL_Rect r = {(int)x + bb_off[0][0], (int)y + bb_off[0][1], m_position.w/3, m_position.h/3};
    bb.push_back(r);
    effect = new Effect("assets/images/effects/Retro_Impact_Effect_Pack_1_F.png", ratio_/3, r, bb_off[0][0], bb_off[0][1]);
    
    initSprite();
    
}

void Sprite::initSprite(){
	m_direction = Direction::NONE;
    m_direction_prev = Direction::DOWN;

    m_spritesheet.select_sprite(0, 0);
    m_spritesheet_column = 0;

    att_dir = Direction::NONE;
    hit=false;
    block = false;
    alive = true;
}

Sprite::~Sprite(){
    delete effect;
    effect = NULL;
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
                    bb_att.clear();
                    bb_att_off.clear();
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
    effect->move(x, y);
    effect->update();
}

void Sprite::meleeAttack(){
    for(auto& player : Game::players){
        if(player->id != id && !hit){
            if(checkCollision2(bb_att, player->bb)){
                hit=true;
                player->take_damage(strength);
            }
        }
    }
}

void Sprite::draw()
{
    m_spritesheet.draw_selected_sprite(renderer, &m_position);
    effect->draw();
    // SDL_RenderDrawRect(renderer, &m_position);
    // SDL_RenderDrawRect(renderer, &bb[0]);
    // if(bb.size() > 1)
    //     SDL_RenderDrawRect(renderer, &bb.back());
}

void bounds(double &p, int bb_p, int bb_s, int bb_off_p, int size_p){
    if(bb_p < 0){p = - bb_off_p;}
    else if( bb_p + bb_s > size_p ){p = size_p - bb_s - bb_off_p;}
}

void Sprite::setPos(double x1, double y1){
    x = x1;
    y = y1;
    move_boxes();
    m_position.x = x;
    m_position.y = y;
}

void Sprite::move(double dx, double dy){
    x += dx;
    move_boxes();

    bounds(x, bb[0].x, bb[0].w, bb_off[0][0], Game::appWindow->WIDTH);
    if(checkCollision2(bb, Game::scene->get_boxes()))
        x -= dx;

    y += dy;
    move_boxes();

    bounds(y, bb[0].y, bb[0].h, bb_off[0][1], Game::appWindow->HEIGHT);
    if(checkCollision2(bb, Game::scene->get_boxes()))
        y -= dy;

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
    for( int i = 0; i < (int)bb_att.size(); i++ )
    {
        bb[i].x = x + bb_att_off[i][0];
        bb[i].y = y + bb_att_off[i][1];
    }
}

std::vector<SDL_Rect>& Sprite::get_boxes()
{
    return bb;
}

void Sprite::change_skin(const char* path){
    m_spritesheet.load_skin(path);
}