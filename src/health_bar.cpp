#include "../include/health_bar.hpp"
#include "../include/game.hpp"
#include "../include/utilities.hpp"
#include "../include/player.hpp"

HealthBar::HealthBar(int x, int y, int width, int height): 
               m_rect({x, y, width, height}), 
               m_renderer(Game::appWindow->renderer)
{
	std::vector<std::string> imagePaths = {	"assets/images/players/health_bar/health_bar_empty.png", 
                                            "assets/images/players/health_bar/health_bar_content.png"};

    for (const auto &imagePath : imagePaths)
    {
        SDL_Surface *surface = load_png(imagePath.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_FreeSurface(surface); surface = NULL;
        m_textures.push_back(texture);
    }
    lifeRect = {m_rect.x + m_rect.w/6, m_rect.y, m_rect.w-m_rect.w/6, m_rect.h};
    // m_rect.y -= 30;
}

HealthBar::~HealthBar()
{
    for (auto& texture : m_textures)
    {
        SDL_DestroyTexture(texture);
    }
    m_textures.clear(); // Clear the vector after destroying the textures
}

void HealthBar::render()
{
    SDL_RenderCopy(m_renderer, m_textures[1], NULL, &lifeRect);
    SDL_RenderCopy(m_renderer, m_textures[0], NULL, &m_rect);
}


void HealthBar::actualDamages(int life, int max_life)
{
    float a = ((float)life/(float)max_life)*(float)(m_rect.w-m_rect.w/6);
    lifeRect.w = (int)a;

}
