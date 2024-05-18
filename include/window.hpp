#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>


class Window {
    
    public:

        SDL_Window *mainWindow = NULL;
        SDL_Renderer *renderer = NULL;

        void createWindow(const char *windowTitle, const int width, const int height);
        ~Window();
        void handleEvents(SDL_Event &event);
        int HEIGHT;
        int WIDTH;


};

#endif // Class Window