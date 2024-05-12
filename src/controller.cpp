#include "../include/controller.hpp"
#include "../include/player.hpp"
#include "../include/game.hpp"

int Controller::id = 0;

SDL_GameController *findController() {
    std::cerr << "bbbbbbb" << std::endl;
    for (int i = Controller::id; i < SDL_NumJoysticks(); i++) {
        std::cerr << "tatat" << std::endl;
        if (SDL_IsGameController(i)) {
            Controller::id = i+1;
            return SDL_GameControllerOpen(i);
        }
    }
    std::cerr << "ccccccccccc" << std::endl;
    SDL_GameControllerClose(nullptr);
    return nullptr;
}

inline SDL_JoystickID getControllerInstanceID(SDL_GameController *controller) {
    return SDL_JoystickInstanceID(
            SDL_GameControllerGetJoystick(controller));
}


Controller::Controller(Player *player_)
{
    player = player_;
    test2 = 1;
    controller = findController();
    std::cerr << controller << std::endl;
}

Controller::~Controller(){
    // std::cerr << "Controller Destructor" << std::endl;
    // delete player;
    // SDL_GameControllerClose(controller);
    // delete controller;
    // if (controller) {
    //     SDL_GameControllerClose(controller);
    // }
}

void Controller::registerWithEventHandler(Event &handler)
{
    handler.registerEvent(SDL_KEYUP, [this](SDL_Event const &event)
                          {
            if (event.key.keysym.sym == SDLK_ESCAPE && player->test == 5) {
                std::cerr << player->test << std::endl;
                Game::stopGame();
                } });
    handler.registerEvent(SDL_QUIT, [this](SDL_Event const &event)
                          {
            std::cerr << "test2" << std::endl; 
            Game::stopGame(); });
}


void Controller::getMove(){
    if (controller) {
            float x = (float) SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) / (float) INT16_MAX;
            float y = (float) SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) / (float) INT16_MAX;
            // renderCross(screenSurface, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, x, y);
            player->move(x, y);
        }

}

