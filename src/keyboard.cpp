#include "../include/keyboard.hpp"
#include "../include/player.hpp"
#include "../include/gamepad.hpp"

int Keyboard::nb_keyboard = 0;

Keyboard::Keyboard() : Controller(){
    Keys["UP"].insert(Keys["UP"].end(),{SDLK_z, SDLK_UP});
    Keys["DOWN"].insert(Keys["DOWN"].end(),{SDLK_s, SDLK_DOWN});
    Keys["RIGHT"].insert(Keys["RIGHT"].end(),{SDLK_d, SDLK_RIGHT});
    Keys["LEFT"].insert(Keys["LEFT"].end(),{SDLK_q, SDLK_LEFT});
    Keys["ATT"].insert(Keys["ATT"].end(),{SDLK_e, SDLK_m});
    Keys["DEF"].insert(Keys["DEF"].end(),{SDLK_r, SDLK_l});
    id = nb_keyboard%2;
    nb_keyboard++;
    ev.push_back(Direction::NONE);
    block = false;
    att = false;
    changeController = false;
};

Keyboard::~Keyboard(){
}

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
            else if(Keys["DEF"][id] == event.key.keysym.sym)
                block = false;
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
            else if(Keys["ATT"][id] == event.key.keysym.sym)
                att = true;
            else if(Keys["DEF"][id] == event.key.keysym.sym)
                block = true;
            break;
        case SDL_CONTROLLERDEVICEADDED:
            changeController = true;
            // if (!controller) {
            //     controller = SDL_GameControllerOpen(event.cdevice.which);
            // }
            break;
    }
}

Controller* Keyboard::switchController(){
    return new Gamepad();
}