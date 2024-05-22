#include "../include/keyboard.hpp"
#include "../include/player.hpp"
#include "../include/gamepad.hpp"

// Initialize static member for counting keyboard instances
int Keyboard::nb_keyboard = 0;

// Constructor for Keyboard class
Keyboard::Keyboard() : Controller() {
    // Initialize key mappings for the keyboard
    Keys["UP"].insert(Keys["UP"].end(), {SDLK_z, SDLK_UP});
    Keys["DOWN"].insert(Keys["DOWN"].end(), {SDLK_s, SDLK_DOWN});
    Keys["RIGHT"].insert(Keys["RIGHT"].end(), {SDLK_d, SDLK_RIGHT});
    Keys["LEFT"].insert(Keys["LEFT"].end(), {SDLK_q, SDLK_LEFT});
    Keys["ATT"].insert(Keys["ATT"].end(), {SDLK_e, SDLK_m});
    Keys["DEF"].insert(Keys["DEF"].end(), {SDLK_r, SDLK_l});

    // Assign unique ID to each keyboard instance
    id = nb_keyboard;
    nb_keyboard++;

    // Initialize event handling and action flags
    ev.push_back(Direction::NONE);
    block = false;
    att = false;
    changeController = false;
}

// Destructor for Keyboard class
Keyboard::~Keyboard() {
    // Destructor does not have any specific tasks
}

// Handle SDL events for the keyboard
void Keyboard::handle_events(SDL_Event const &event) {
    switch (event.type) {
        // Handle key release events
        case SDL_KEYUP:
            if (Keys["UP"][id] == event.key.keysym.sym)
                ev.erase(std::remove(ev.begin(), ev.end(), Direction::UP), ev.end());
            else if (Keys["DOWN"][id] == event.key.keysym.sym)
                ev.erase(std::remove(ev.begin(), ev.end(), Direction::DOWN), ev.end());
            else if (Keys["LEFT"][id] == event.key.keysym.sym)
                ev.erase(std::remove(ev.begin(), ev.end(), Direction::LEFT), ev.end());
            else if (Keys["RIGHT"][id] == event.key.keysym.sym)
                ev.erase(std::remove(ev.begin(), ev.end(), Direction::RIGHT), ev.end());
            else if (Keys["DEF"][id] == event.key.keysym.sym)
                block = false;
            break;

        // Handle key press events
        case SDL_KEYDOWN:
            if (Keys["UP"][id] == event.key.keysym.sym)
                ev.push_back(Direction::UP);
            else if (Keys["DOWN"][id] == event.key.keysym.sym)
                ev.push_back(Direction::DOWN);
            else if (Keys["LEFT"][id] == event.key.keysym.sym)
                ev.push_back(Direction::LEFT);
            else if (Keys["RIGHT"][id] == event.key.keysym.sym)
                ev.push_back(Direction::RIGHT);
            else if (Keys["ATT"][id] == event.key.keysym.sym)
                att = true;
            else if (Keys["DEF"][id] == event.key.keysym.sym)
                block = true;
            break;

        // Handle game controller connection events
        case SDL_CONTROLLERDEVICEADDED:
            changeController = true;
            nb_keyboard--;
            break;
    }
}

// Switch from keyboard to gamepad controller
Controller* Keyboard::switchController() {
    return new Gamepad(); // Return a new Gamepad instance
}
