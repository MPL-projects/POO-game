#include "../include/player.hpp"

void Player::handle_events(SDL_Event const &event)
{
    if(controller->ev.back() != Direction::NONE)
        m_direction_prev = controller->ev.back();
    controller->handle_events(event);
    m_direction = controller->ev.back();
}

