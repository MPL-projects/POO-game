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
    Menu();
    ~Menu(); // Destructor to handle cleanup

    void displayMenu();
    void handleEvents(SDL_Event &event);
    void addButton(Button* button); // Function to add buttons to the menu
    bool buttonStatus(Button* button);
    void setBackground(const std::string&  imagePath);

private:
    std::vector<Button*> buttons;
    SDL_Renderer *m_renderer;
    SDL_Texture *back_texture;

    int windowHeight, windowWidth;

    void destroyMenuScreen();
    void render_background();
};

#endif
