#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class Menu {
    public:

        Menu(SDL_Renderer *windowsplashFontRenderer, SDL_Window *window);
        void initSplashScreen(const char *displayName, const char *fontFamily, const char *backgroundImg = NULL);
        void displaySplashScreen();
        void quitSplashScreen();

    private:
        SDL_Window *windowScreen;
        SDL_Renderer *splashFontRenderer, *splashImageRenderer;
        SDL_Texture *splashFontTexture, *splashImageTexture;
        SDL_Surface *splashFontSurface;
        TTF_Font *splashFont;
        const char *splashText;

        int windowHeight, windowWidth, splashScreenTextBlink;
        void prepareSplashScreen(const char *displayName, const char *fontFamily, const char *backgroundImg);
        void renderSplashScreenText();
        void renderSplashBackground();
        void renderSplashScreen();
        void destroySplashScreen();

};

#endif //Class Menu