#include "../include/player.hpp"

void Player::handle_events(SDL_Event const &event)
{
    controller->handle_events(event);
}

