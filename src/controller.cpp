#include "../include/controller.hpp"
#include "../include/player.hpp"
#include "../include/game.hpp"

int Controller::id = 0;

Controller::Controller(Player *player_)
{
    player = player_;
}

// void Controller::registerWithEventHandler(Event &handler)
// {
//     handler.registerEvent(SDL_KEYUP, [this](SDL_Event const &event)
//                           {
//             if (event.key.keysym.sym == SDLK_ESCAPE && player->test == 5) {
//                 Game::stopGame();
//                 } });
//     handler.registerEvent(SDL_QUIT, [this](SDL_Event const &event)
//                           {
//             Game::stopGame(); });
// }




