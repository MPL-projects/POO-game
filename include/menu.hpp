#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


using namespace std;

class Menu {
    public:

        Menu(SDL_Renderer *menuFontRenderer, SDL_Window *window);

        /*First screen*/
        void displaySplashScreen();
        void quitSplashScreen();


        /*Seconde screen*/
        void displayMenu();
        // void quitMenu();

    private:
        SDL_Window *windowScreen;
        SDL_Renderer *splashFontRenderer, *splashImageRenderer, *menu_renderer;
        SDL_Texture *splashFontTexture, *splashImageTexture;
        SDL_Surface *splashFontSurface;
        TTF_Font *splashFont;
        const char *splashText;

        int windowHeight, windowWidth, splashScreenTextBlink;

        /*First screen*/
        void initSplashScreen(const char *displayName, const char *fontFamily, const char *backgroundImg = NULL);
        void prepareSplashScreen(const char *displayName, const char *fontFamily, const char *backgroundImg);
        void renderSplashScreenText();
        void renderSplashBackground();
        void renderSplashScreen();
        void destroySplashScreen();


};

#endif //Class Menu