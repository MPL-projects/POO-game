// menu.hpp
#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdexcept> 
#include <vector>
#include "../include/button.hpp"

class Menu {
public:
    Menu(SDL_Renderer *menuFontRenderer, SDL_Window *window);
    ~Menu(); // Destructor to handle cleanup

    void displayMenu(const std::string& backPath);
    void handleEvents(SDL_Event &event);
    void addButton(Button* button); // Function to add buttons to the menu
    bool buttonStatus(Button* button);

private:
    SDL_Window *windowScreen;
    std::vector<Button*> buttons;
    SDL_Renderer *m_renderer;
    SDL_Texture *back_texture;

    int windowHeight, windowWidth;

    void backgroundMenuScreen(const std::string&  imagePath);
    void destroyMenuScreen();
};

#endif
