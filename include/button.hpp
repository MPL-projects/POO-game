#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;

class Button {
public:
    Button(int x, int y, int width, int height, const vector<string>& imagePaths, const string& fontPath, const string& name, int a);
    ~Button();
    int get_x() const {return m_rect.x;};
    int get_y() const {return m_rect.y;};
    int get_w() const {return m_rect.w;};
    int get_h() const {return m_rect.h;};
    void handleEvent(const SDL_Event& event); 
    void render();

    bool isPressed() const;

private:
    SDL_Rect m_rect;
    vector<SDL_Texture*> m_textures;
    SDL_Renderer* m_renderer;
    int m_currentTextureIndex;
    TTF_Font* m_font;
    SDL_Texture* m_textTexture;

    bool m_isPressed;
    int action;

};

#endif