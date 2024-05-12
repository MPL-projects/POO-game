// main.cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/window.hpp"
#include "../include/menu.hpp"
#include "../include/button.hpp"

int main(int argc, char *argv[]) {
    bool quit = false;
    SDL_Event event;
    Window appWindow;
    appWindow.createWindow("Menu", 800, 600);
    Menu engineMenu(appWindow.renderer, appWindow.mainWindow);

    // Create and add buttons to the menu
    std::vector<std::string> buttonImagePaths = { "assets/images/backgrounds_elements/menu/buttons/button_normal.png", "assets/images/backgrounds_elements/menu/buttons/button_hover.png", "assets/images/backgrounds_elements/menu/buttons/button_pressed.png" };
    Button* playButton = new Button(appWindow.renderer, 100, 100, 160, 80, buttonImagePaths , "assets/ttf/liberation.ttf", "Play");
    engineMenu.addButton(playButton);

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if((event.type==SDL_WINDOWEVENT && event.window.event==SDL_WINDOWEVENT_CLOSE)||(event.type == SDL_QUIT) ){
                quit = true;
            }
            engineMenu.handleEvents(event); // Handle events for buttons
            playButton->isPressed();
        }

        SDL_RenderClear(appWindow.renderer);
        engineMenu.displayMenu();
        SDL_Delay(20);
    }

    // Cleanup
    delete playButton;
    appWindow.destroyWindow();
    return 0;
}
