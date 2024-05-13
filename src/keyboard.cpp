#include "../include/keyboard.hpp"
#include "../include/player.hpp"

int Keyboard::nb_keyboard = 0;

Keyboard::Keyboard() : Controller(){
    Keys["UP"].insert(Keys["UP"].end(),{SDLK_z, SDLK_UP});
    Keys["DOWN"].insert(Keys["DOWN"].end(),{SDLK_s, SDLK_DOWN});
    Keys["RIGHT"].insert(Keys["RIGHT"].end(),{SDLK_d, SDLK_RIGHT});
    Keys["LEFT"].insert(Keys["LEFT"].end(),{SDLK_q, SDLK_LEFT});
    id = nb_keyboard;
    nb_keyboard++;
    ev.push_back(Direction::NONE);
};

Keyboard::~Keyboard(){
    std::cerr << "Keyboard destructor" << std::endl;
}

void Keyboard::setKeys(){
    
}


// void Keyboard::handle_events(SDL_Event const &event)
// {
//     switch(event.type)
//     {
//         case SDL_KEYUP:
//             if(player->m_direction != Direction::NONE){
//                 if(Keys["UP"][id] == event.key.keysym.sym || Keys["DOWN"][id] == event.key.keysym.sym || Keys["LEFT"][id] == event.key.keysym.sym || Keys["RIGHT"][id] == event.key.keysym.sym){
//                     player->m_direction_prev = player->m_direction;
//                     player->m_direction = Direction::NONE;
//                 }
//             }
//             break;
//         case SDL_KEYDOWN:
//             if(Keys["UP"][id] == event.key.keysym.sym)
//                 player->m_direction = Direction::UP;
//             else if(Keys["DOWN"][id] == event.key.keysym.sym)
//                 player->m_direction = Direction::DOWN;
//             else if(Keys["LEFT"][id] == event.key.keysym.sym)
//                 player->m_direction = Direction::LEFT;
//             else if(Keys["RIGHT"][id] == event.key.keysym.sym)
//                 player->m_direction = Direction::RIGHT;
//             break;
//     }
// }

// vec.erase(std::remove(vec.begin(), vec.end(), 8), vec.end());

void Keyboard::handle_events(SDL_Event const &event)
{
    switch(event.type)
    {
        case SDL_KEYUP:
            if(Keys["UP"][id] == event.key.keysym.sym)
                ev.erase(std::remove(ev.begin(), ev.end(), Direction::UP), ev.end());
            else if(Keys["DOWN"][id] == event.key.keysym.sym)
                ev.erase(std::remove(ev.begin(), ev.end(), Direction::DOWN), ev.end());
            else if(Keys["LEFT"][id] == event.key.keysym.sym)
                ev.erase(std::remove(ev.begin(), ev.end(), Direction::LEFT), ev.end());
            else if(Keys["RIGHT"][id] == event.key.keysym.sym)
                ev.erase(std::remove(ev.begin(), ev.end(), Direction::RIGHT), ev.end());
            break;
            break;
        case SDL_KEYDOWN:
            if(Keys["UP"][id] == event.key.keysym.sym)
                ev.push_back(Direction::UP);
            else if(Keys["DOWN"][id] == event.key.keysym.sym)
                ev.push_back(Direction::DOWN);
            else if(Keys["LEFT"][id] == event.key.keysym.sym)
                ev.push_back(Direction::LEFT);
            else if(Keys["RIGHT"][id] == event.key.keysym.sym)
                ev.push_back(Direction::RIGHT);
            break;
    }
}