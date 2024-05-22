#include "../include/gamepad.hpp"
#include "../include/game.hpp"
#include "../include/keyboard.hpp"

// Initialize static member for gamepad ID
int Gamepad::id_gamepad = 0;

// Constructor for Gamepad class
Gamepad::Gamepad() : Controller() {
    connect();  // Attempt to connect the gamepad
    ev.push_back(Direction::NONE);  // Initialize the event vector with no direction
    block = false;  // Initialize block action to false
    att = false;  // Initialize attack action to false
}

// Destructor for Gamepad class
Gamepad::~Gamepad() {
    SDL_GameControllerClose(controller);  // Close the gamepad controller
    controller = nullptr;  // Set the controller to nullptr
}

// Handle SDL events for the gamepad
void Gamepad::handle_events(SDL_Event const &event) {
    float x, y;
    switch(event.type)
    {
        // Handle joystick motion
        case SDL_CONTROLLERAXISMOTION:
            x = (float) SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) / (float) INT16_MAX;
            y = (float) SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) / (float) INT16_MAX;
            setDir(x, y);  // Set the direction based on joystick input
            break;
        
        // Handle button press events
        case SDL_CONTROLLERBUTTONDOWN:
            if (controller && event.cdevice.which == getControllerInstanceID(controller)) {
                switch (event.cbutton.button) {
                    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A:
                        block = true;  // Set block action to true
                        break;
                    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X:
                        att = true;  // Set attack action to true
                        break;
                }
            }
            break;

        // Handle button release events
        case SDL_CONTROLLERBUTTONUP:
            if (controller && event.cdevice.which == getControllerInstanceID(controller)) {
                switch (event.cbutton.button) {
                    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A:
                        block = false;  // Set block action to false
                        break;
                }
            }
            break;

        // Handle gamepad disconnection
        case SDL_CONTROLLERDEVICEREMOVED:
            if (controller && event.cdevice.which == getControllerInstanceID(controller)) {
                SDL_GameControllerClose(controller);  // Close the gamepad controller
                id_gamepad--;  // Decrease the gamepad ID counter
                connect();  // Attempt to reconnect the gamepad
            }
            break;
    }
}

// Set the direction based on joystick input
void Gamepad::setDir(float x, float y) {
    ev.clear();  // Clear the current events
    ev.push_back(Direction::NONE);  // Add no direction as the initial state
    float dead_zone = 0.5;  // Define the dead zone threshold

    if(max(abs(x),abs(y)) > dead_zone) {
        if(abs(x) > abs(y)) {
            if(x > 0.05) {
                ev.push_back(Direction::RIGHT);  // Move right
            } else if(x < dead_zone) {
                ev.push_back(Direction::LEFT);  // Move left
            }
        } else {
            if(y > dead_zone) {
                ev.push_back(Direction::DOWN);  // Move down
            } else if(y < dead_zone) {
                ev.push_back(Direction::UP);  // Move up
            }
        }
    }
}

// Connect the gamepad
void Gamepad::connect() {
    changeController = false;
    controller = findController();  // Find and connect a gamepad controller
    if(controller == nullptr)
        changeController = true;  // If no controller is found, set changeController to true
}

// Switch to keyboard controller
Controller* Gamepad::switchController() {
    SDL_GameControllerClose(controller);  // Close the gamepad controller
    controller = nullptr;  // Set the controller to nullptr
    return new Keyboard();  // Return a new Keyboard controller
}

// Find and open a gamepad controller
SDL_GameController* Gamepad::findController() {
    for (int i = id_gamepad; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            id_gamepad++;
            return SDL_GameControllerOpen(i);  // Open and return the gamepad controller
        }
    }
    SDL_GameControllerClose(nullptr);
    return nullptr;  // Return nullptr if no gamepad controller is found
}

// Get the instance ID of the gamepad controller
inline SDL_JoystickID Gamepad::getControllerInstanceID(SDL_GameController *controller) {
    return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));  // Return the joystick instance ID
}
