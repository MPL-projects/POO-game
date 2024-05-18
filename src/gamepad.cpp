#include "../include/gamepad.hpp"
#include "../include/game.hpp"

SDL_GameController *findController() {
    for (int i = Controller::id; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            Controller::id = i+1;
            return SDL_GameControllerOpen(i);
        }
    }
    SDL_GameControllerClose(nullptr);
    return nullptr;
}

inline SDL_JoystickID getControllerInstanceID(SDL_GameController *controller) {
    return SDL_JoystickInstanceID(
            SDL_GameControllerGetJoystick(controller));
}

Gamepad::Gamepad() : Controller(){
    controller = findController();
    ev.push_back(Direction::NONE);
    block = false;
    att = false;
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

// void Gamepad::getMove(){
//     if (controller) {
//             // float x = (float) SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) / (float) INT16_MAX;
//             // float y = (float) SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) / (float) INT16_MAX;
//             // renderCross(screenSurface, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, x, y);
//             // player->move(x, y);
//         }

// }