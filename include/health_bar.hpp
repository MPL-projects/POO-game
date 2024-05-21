#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "player.hpp"

using namespace std;

class HealthBar {
public:
    HealthBar(int x, int y, int width, int height);
    ~HealthBar();

    int get_x() const {return m_rect.x;};
    int get_y() const {return m_rect.y;};
    int get_w() const {return m_rect.w;};
    int get_h() const {return m_rect.h;};

	void actualDamages(int life, int max_life);
    
    void render();

private:
    SDL_Rect m_rect;
    SDL_Rect lifeRect;
    vector<SDL_Texture*> m_textures;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_textTexture;
};

#endif