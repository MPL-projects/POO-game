#include "../include/player.hpp"

int Player::nb_players = 0;
Player::Player(SDL_Renderer *renderer) : StickFigure(renderer)
{
    controller = new Keyboard();
    life = 100;
    strength = 10;
    id = nb_players;
    nb_players++;
}

void Player::handle_events(SDL_Event const &event)
{
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
}

void Player::initMeleeAttack(){
    att_dir = m_direction;
    m_spritesheet_column = 0;
    if(att_dir==Direction::NONE)
        att_dir = m_direction_prev;
    SDL_Rect att_bb;
    std::vector<int> att_bb_off;

    int r_w = bb[0].w;
    int r_h = 30;
    switch(att_dir){
        case Direction::UP:
            att_bb_off = {bb_off[0][0], bb_off[0][1]-r_h};
            att_bb = {(int)x + att_bb_off[0], (int)y + att_bb_off[1], r_w, r_h};
            break;
        case Direction::DOWN:
            att_bb_off = {bb_off[0][0], bb_off[0][1]+bb[0].h};
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
    bb.push_back(att_bb);
    bb_off.push_back(att_bb_off);
}
