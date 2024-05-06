#include "../include/menu.hpp"

Menu::Menu(SDL_Renderer *windowsplashFontRenderer, SDL_Window *window){
    TTF_Init();
    splashFontRenderer = windowsplashFontRenderer;
    windowScreen = window;
    splashScreenTextBlink = 0;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
}

void Menu::initSplashScreen(const char *displayName, const char *fontFamily, const char *backgroundImg){
    prepareSplashScreen(displayName, fontFamily, backgroundImg);
    
}

void Menu::displaySplashScreen(){
    renderSplashScreen();
}

void Menu::quitSplashScreen(){
    destroySplashScreen();
}



void Menu::prepareSplashScreen(const char *displayName, const char *fontFamily, const char *backgroundImg){
    splashFont = TTF_OpenFont(fontFamily, 25);
    splashText = displayName;

    if(backgroundImg != NULL){
        
        splashImageRenderer = SDL_CreateRenderer(windowScreen, -1, 0);
        SDL_Surface *splashBackgroundSurface = SDL_LoadBMP(backgroundImg);
        splashImageTexture = SDL_CreateTextureFromSurface(splashFontRenderer, splashBackgroundSurface);

    }
}


void Menu::renderSplashScreenText(){
    int textWidth = 0;
    int textHeight = 0;

    SDL_Color color = {255, 255, 255};
    splashFontSurface = TTF_RenderText_Solid(splashFont, splashText, color);
    splashFontTexture = SDL_CreateTextureFromSurface(splashFontRenderer, splashFontSurface);

    splashScreenTextBlink++;
    if(splashScreenTextBlink == 100){

        splashScreenTextBlink = 0;
        
    }

    //Handle splash screen text blinkg effect
    if(splashScreenTextBlink < 50){

        SDL_QueryTexture(splashFontTexture, NULL, NULL, &textWidth, &textHeight);

        const int devideScreenWidth = windowWidth / 2;
        const int deviceText = textWidth / 2;
        const int dediceScreenHeight = windowHeight / 2;

        SDL_Rect fontStruct = {devideScreenWidth - deviceText, dediceScreenHeight, textWidth, textHeight };                
        SDL_RenderCopy(splashFontRenderer, splashFontTexture, NULL, &fontStruct);

    }else{

        splashFontTexture = NULL;
        splashFontSurface = NULL;

    }
}

void Menu::renderSplashBackground(){
    SDL_RenderCopy(splashFontRenderer, splashImageTexture, NULL, NULL);
    SDL_RenderPresent(splashFontRenderer);
}

void Menu::renderSplashScreen(){
    renderSplashBackground();
    renderSplashScreenText();
    

}

void Menu::destroySplashScreen(){

    SDL_DestroyTexture(splashFontTexture);
    SDL_FreeSurface(splashFontSurface);

}


