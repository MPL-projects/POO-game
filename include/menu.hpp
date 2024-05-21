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

    void displayMenu(bool var = true);
    void handleEvents(SDL_Event &event);
    void addButton(Button* button); // Function to add buttons to the menu
    bool buttonStatus(Button* button);
    void setBackground(const std::string&  imagePath);
    SDL_Texture* getBackground(){return back_texture;};

    SDL_Renderer *m_renderer;

private:
    std::vector<Button*> buttons;
    SDL_Texture *back_texture;

    int windowHeight, windowWidth;

    void render_background();
};

#endif
