#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdexcept>
#include <vector>

class Button {
private:
    SDL_Rect m_rect;
    std::vector<SDL_Texture*> m_textures;
    SDL_Renderer* m_renderer;
    int m_currentTextureIndex;
    TTF_Font* m_font;
    SDL_Texture* m_textTexture;

    bool m_isPressed;

public:
    int get_x() const {return m_rect.x;};
    int get_y() const {return m_rect.y;};
    int get_w() const {return m_rect.w;};
    int get_wh() const {return m_rect.h;};
    Button(SDL_Renderer* renderer, int x, int y, int width, int height, const std::vector<std::string>& imagePaths, const std::string& fontPath);
    ~Button();
    void handleEvent(const SDL_Event& event); 
    void render();

    bool isPressed() const { return m_isPressed; }
};

#endif //Class Button