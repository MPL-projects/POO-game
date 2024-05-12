#include "../include/keyboard.hpp"
#include "../include/player.hpp"

int Keyboard::nb_keyboard = 0;

Keyboard::Keyboard(Player *player_) : Controller(player_){
    Keys["UP"].insert(Keys["UP"].end(),{SDLK_z, SDLK_UP});
    Keys["DOWN"].insert(Keys["DOWN"].end(),{SDLK_s, SDLK_DOWN});
    Keys["RIGHT"].insert(Keys["RIGHT"].end(),{SDLK_d, SDLK_RIGHT});
    Keys["LEFT"].insert(Keys["LEFT"].end(),{SDLK_q, SDLK_LEFT});
    id = nb_keyboard;
    nb_keyboard++;
};

Keyboard::~Keyboard(){
    std::cerr << "Keyboard destructor" << std::endl;
}

void Keyboard::setKeys(){
    
}

void Keyboard::handle_events(SDL_Event const &event)
{
    switch(event.type)
    {
        case SDL_KEYUP:
            if(player->m_direction != Direction::NONE){
                if(Keys["UP"][id] == event.key.keysym.sym || Keys["DOWN"][id] == event.key.keysym.sym || Keys["LEFT"][id] == event.key.keysym.sym || Keys["RIGHT"][id] == event.key.keysym.sym){
                    player->m_direction_prev = player->m_direction;
                    player->m_direction = Direction::NONE;
                }
            }
            break;
        case SDL_KEYDOWN:
            if(Keys["UP"][id] == event.key.keysym.sym)
                player->m_direction = Direction::UP;
            else if(Keys["DOWN"][id] == event.key.keysym.sym)
                player->m_direction = Direction::DOWN;
            else if(Keys["LEFT"][id] == event.key.keysym.sym)
                player->m_direction = Direction::LEFT;
            else if(Keys["RIGHT"][id] == event.key.keysym.sym)
                player->m_direction = Direction::RIGHT;
            break;
    }
}