// menu.cpp
#include "../include/menu.hpp"

Menu::Menu(SDL_Renderer *menuFontRenderer, SDL_Window *window)
{
    TTF_Init();
    m_renderer = menuFontRenderer;
    windowScreen = window;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

}

Menu::~Menu() {
    destroyMenuScreen();
    for (auto button : buttons) {
        delete button;
    }
    TTF_Quit();
}

void Menu::displayMenu(const std::string& backPath) {
    backgroundMenuScreen(backPath);
    for(auto button : buttons) {
        button->render(); // Render each button
    }
    // SDL_RenderPresent(m_renderer);
}

void Menu::backgroundMenuScreen(const std::string&  imagePath) {
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        throw std::runtime_error("Failed to load image: " + imagePath);
    }
    back_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(m_renderer, back_texture, NULL, NULL);
}

void Menu::destroyMenuScreen() {
    if (back_texture) {
        SDL_DestroyTexture(back_texture);
        back_texture = nullptr;
    }
}

void Menu::handleEvents(SDL_Event &event) {
    // Handle events for buttons or other interactive elements
    std::cout<< event.type << "\n";
    for(auto button : buttons) {
        button->handleEvent(event);
    }
}

void Menu::addButton(Button* button) {
    buttons.push_back(button);
}

bool buttonStatus(Button* button){
    return button->isPressed();
}