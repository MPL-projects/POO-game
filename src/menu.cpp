// menu.cpp
#include "../include/menu.hpp"
#include "../include/utilities.hpp"
#include "../include/game.hpp"

// Constructor for Menu class
Menu::Menu()
{
    TTF_Init();  // Initialize the TTF library for font rendering
    m_renderer = Game::appWindow->renderer;  // Get the renderer from the game window
    windowWidth = Game::appWindow->HEIGHT;  // Set window height
    windowHeight = Game::appWindow->WIDTH;  // Set window width
    // Add a default background texture (e.g., white rectangle)
}

// Destructor for Menu class
Menu::~Menu() {
    for (auto& button : buttons) {
        delete button;  // Delete each button to free memory
    }
    buttons.clear();  // Clear the buttons vector
    SDL_DestroyTexture(back_texture);  // Destroy the background texture
    back_texture = nullptr;  // Set the texture pointer to nullptr
    TTF_Quit();  // Quit the TTF library
}

// Display the menu, optionally rendering the background
void Menu::displayMenu(bool var) {
    if (var == true) {
        render_background();  // Render the background if var is true
    }
    
    for (auto button : buttons) {
        button->render();  // Render each button
    }
}

// Set the background texture for the menu
void Menu::setBackground(const std::string& imagePath) {
    SDL_Surface* surface = load_png(imagePath.c_str());  // Load the background image
    back_texture = SDL_CreateTextureFromSurface(m_renderer, surface);  // Create a texture from the surface
    SDL_FreeSurface(surface);  // Free the surface
    surface = nullptr;  // Set the surface pointer to nullptr
    SDL_RenderCopy(m_renderer, back_texture, nullptr, nullptr);  // Copy the texture to the renderer
}

// Render the background texture
void Menu::render_background() {
    SDL_RenderCopy(m_renderer, back_texture, nullptr, nullptr);  // Copy the texture to the renderer
}

// Handle events for the menu
void Menu::handleEvents(SDL_Event &event) {
    // Handle events for buttons or other interactive elements
    for (auto button : buttons) {
        button->handleEvent(event);  // Handle the event for each button
    }
}

// Add a button to the menu
void Menu::addButton(Button* button) {
    buttons.push_back(button);  // Add the button to the buttons vector
}

// Check if a button is pressed
bool Menu::buttonStatus(Button* button) {
    return button->isPressed();  // Return the button's pressed status
}
