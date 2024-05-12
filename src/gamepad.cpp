#include "../include/gamepad.hpp"
#include "../include/player.hpp"
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

Gamepad::Gamepad(Player *player_) : Controller(player_){
    controller = findController();
}

void Gamepad::getMove(){
    if (controller) {
            float x = (float) SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) / (float) INT16_MAX;
            float y = (float) SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) / (float) INT16_MAX;
            // renderCross(screenSurface, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, x, y);
            player->move(x, y);
        }

}