#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "../include/window.hpp"

#include "../include/menu.hpp"

#include "../include/button.hpp"


using namespace std;

bool menu = false;

int main(int argc, char *argv[]){

    bool quit = false;

    SDL_Event event;

    Window appWindow;
    appWindow.createWindow("Menu", 800, 600);

    Menu engineMenu(appWindow.renderer, appWindow.mainWindow);

    while (!quit){

        SDL_PollEvent(&event);
        if((event.type==SDL_WINDOWEVENT && event.window.event==SDL_WINDOWEVENT_CLOSE)||(event.type == SDL_QUIT)){
            quit = true;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
            std::cout << "Enter key pressed!" << std::endl;
            menu = true;
            engineMenu.quitSplashScreen();

            

            //init the game
            // engineMenu.initMenu();

        }


        //clear the render
        SDL_RenderClear(appWindow.renderer);

        if (menu){
            engineMenu.displayMenu();
        }else{
            //render the splash screen
            engineMenu.displaySplashScreen();
        }
        

        //render the new texture
        SDL_RenderPresent(appWindow.renderer);
        SDL_Delay(20);
    }

    
    engineMenu.quitSplashScreen();

    appWindow.destroyWindow();

    return 0;

}