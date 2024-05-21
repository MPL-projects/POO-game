// menu.cpp
#include "../include/menu.hpp"
#include "../include/utilities.hpp"
#include "../include/game.hpp"

Menu::Menu()
{
    TTF_Init();
    m_renderer = Game::appWindow->renderer;
    windowWidth = Game::appWindow->HEIGHT;
    windowHeight = Game::appWindow->WIDTH;
    //add a default background texture (white rectangle for example)
}

Menu::~Menu() {
    for (auto& button : buttons) {
        delete button;
    }
    buttons.clear();
    SDL_DestroyTexture(back_texture);
    back_texture = NULL;
    TTF_Quit();
}

void Menu::displayMenu(bool var) {
	if (var == true){
		render_background();
	}
    
    for(auto button : buttons) {
        button->render(); // Render each button
    }
}

void Menu::setBackground(const std::string&  imagePath) {
    SDL_Surface* surface = load_png(imagePath.c_str());
    back_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);
    surface = NULL;
    SDL_RenderCopy(m_renderer, back_texture, NULL, NULL);
}

void Menu::render_background() {
    SDL_RenderCopy(m_renderer, back_texture, NULL, NULL);
}

void Menu::handleEvents(SDL_Event &event) {
    // Handle events for buttons or other interactive elements
    for(auto button : buttons) {
        button->handleEvent(event);
    }
}

void Menu::addButton(Button* button) {
    buttons.push_back(button);
}

bool Menu::buttonStatus(Button* button){
    return button->isPressed();
}