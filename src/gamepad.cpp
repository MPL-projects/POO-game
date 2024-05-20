#include "../include/gamepad.hpp"
#include "../include/game.hpp"
#include "../include/keyboard.hpp"

int Gamepad::id_gamepad = 0;

Gamepad::Gamepad() : Controller(){
    connect();
    ev.push_back(Direction::NONE);
    block = false;
    att = false;
}

Gamepad::~Gamepad(){
    SDL_GameControllerClose(controller);
    controller = NULL;
}

void Gamepad::handle_events(SDL_Event const &event){
    float x, y;
    switch(event.type)
    {
        case SDL_CONTROLLERAXISMOTION:
            x = (float) SDL_GameControllerGetAxis(controller,
                SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) / (float) INT16_MAX;
            y = (float) SDL_GameControllerGetAxis(controller,
                SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) / (float) INT16_MAX;
            setDir(x, y);
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            if (controller && event.cdevice.which == getControllerInstanceID(controller)) {
                switch (event.cbutton.button) {
                    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A:
                        block = true;
                        break;
                    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X:
                        att = true;
                        break;
                }
            }
            break;
        case SDL_CONTROLLERBUTTONUP:
            if (controller && event.cdevice.which == getControllerInstanceID(controller)) {
                switch (event.cbutton.button) {
                    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A:
                        block = false;
                        break;
                }
            }
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            if (controller && event.cdevice.which == getControllerInstanceID(controller)) {
                SDL_GameControllerClose(controller);
                id_gamepad--;
                connect();
            }
            break;
    }

}

void Gamepad::setDir(float x, float y){
    ev.clear();
    ev.push_back(Direction::NONE);
    float dead_zone = 0.5;
    if(max(abs(x),abs(y))>dead_zone){
        if(abs(x) > abs(y)){
            if(x > 0.05){
                ev.push_back(Direction::RIGHT);
            }
            else if(x<dead_zone){
                ev.push_back(Direction::LEFT);
            }
        }
        else{
            if(y > dead_zone){
                ev.push_back(Direction::DOWN);
            }
            else if(y<dead_zone){
                ev.push_back(Direction::UP);
            }
        }
    }
}

void Gamepad::connect(){
    changeController = false;
    controller = findController();
    if(controller == nullptr)
        changeController = true;
}

Controller* Gamepad::switchController(){
    SDL_GameControllerClose(controller);
    controller = NULL;
    return new Keyboard();
}

SDL_GameController* Gamepad::findController() {
    for (int i = id_gamepad; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            id_gamepad++;
            return SDL_GameControllerOpen(i);
        }
    }
    SDL_GameControllerClose(nullptr);
    return nullptr;
}

inline SDL_JoystickID Gamepad::getControllerInstanceID(SDL_GameController *controller) {
    return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
}
