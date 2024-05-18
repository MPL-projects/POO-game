#include "../include/player.hpp"

int Player::nb_players = 0;
Player::Player(const char* path_to_sprite, float ratio_) : Sprite(path_to_sprite, ratio_)
{
    // controller = new Keyboard();
    controller = new Keyboard();
    life = 100;
    strength = 10;
    id = nb_players;
    nb_players++;
}

void Player::handle_events(SDL_Event const &event)
{
    if(alive){
        if (controller->ev.back() != Direction::NONE)
            m_direction_prev = controller->ev.back();
        controller->handle_events(event);
        m_direction = controller->ev.back();
        if(att_dir != Direction::NONE)
            controller->att = false;
        if (controller->att){
            controller->att = false;
            initMeleeAttack();
        }
        if(controller->block)
            block = true;
        else
            block = false;
    }
}


void Player::initMeleeAttack(){
    att_dir = m_direction;
    m_spritesheet_column = 0;
    if(att_dir==Direction::NONE)
        att_dir = m_direction_prev;
    SDL_Rect att_bb;
    std::vector<int> att_bb_off;

    int r_w = bb[0].h;
    int r_h = bb[0].w/2;
    switch(att_dir){
        case Direction::NONE:
            break;
        case Direction::UP:
            att_bb_off = {bb_off[0][0]+(bb[0].w-r_w)/2, bb_off[0][1]-3*r_h/5};
            att_bb = {(int)x + att_bb_off[0], (int)y + att_bb_off[1], r_w, r_h};
            break;
        case Direction::DOWN:
            att_bb_off = {bb_off[0][0]+(bb[0].w-r_w)/2, bb_off[0][1]+bb[0].h-r_h/2};
            att_bb = {(int)x + att_bb_off[0], (int)y + att_bb_off[1], r_w, r_h};
            break;
        case Direction::LEFT:
            att_bb_off = {bb_off[0][0]-r_h, bb_off[0][1]+(bb[0].h-r_w)/2};
            att_bb = {(int)x + att_bb_off[0], (int)y + att_bb_off[1], r_h, r_w};
            break;
        case Direction::RIGHT:
            att_bb_off = {bb_off[0][0] + bb[0].w, bb_off[0][1]+(bb[0].h-r_w)/2};
            att_bb = {(int)x + att_bb_off[0], (int)y + att_bb_off[1], r_h, r_w};
            break;
    }
    bb_att.push_back(att_bb);
    bb_att_off.push_back(att_bb_off);
}

void Player::take_damage(int damages){
    if(!block){
        life -= damages;
        if(life <= 0){
            alive = false;
            life = 0;
            m_spritesheet_column = 0;
        }
    }
    effect->show = true;
}
