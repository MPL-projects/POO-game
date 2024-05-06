#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "../include/window.hpp"

#include "../include/menu.hpp"

using namespace std;


int main(int argc, char *argv[]){

    bool quit = false;

    SDL_Event event;

    Window appWindow;
    appWindow.createWindow("Menu Demonstration", 800, 600);

    Menu engineMenu(appWindow.renderer, appWindow.mainWindow);

    //init the splash screen
    engineMenu.initSplashScreen("Press Enter to start", "assets/ttf/liberation.ttf", "assets/images/backgrounds_elements/menu/background.bmp");

    while (!quit){

        SDL_PollEvent(&event);
        if(event.type==SDL_WINDOWEVENT && event.window.event==SDL_WINDOWEVENT_CLOSE){
            quit = true;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
            std::cout << "Enter key pressed!" << std::endl;
            //engineMenu.initSplashScreen("Ready !! ", "assets/ttf/liberation.ttf", "assets/images/backgrounds_elements/grass.png");
        }

        //clear the render
        SDL_RenderClear(appWindow.renderer);

        //render the splash screen
        engineMenu.displaySplashScreen();

        //render the new texture
        SDL_RenderPresent(appWindow.renderer);
        SDL_Delay(20);
    }

    
    engineMenu.quitSplashScreen();

    appWindow.destroyWindow();

    return 0;

}