#include "../include/controller.hpp"
#include "../include/player.hpp"

Controller::Controller(Player *player_)
{
    player = player_;
}

void Controller::registerWithEventHandler(Event &handler)
{
    handler.registerEvent(SDL_KEYUP, [this](SDL_Event const &event)
                          {
            if (event.key.keysym.sym == SDLK_ESCAPE && player->test == 6) {
                std::cerr << player->test << std::endl;
                Game::stopGame();
                } });
    handler.registerEvent(SDL_QUIT, [this](SDL_Event const &event)
                          {
            std::cerr << "test2" << std::endl; 
            Game::stopGame(); });
}