#include "../include/health_bar.hpp"
#include "../include/game.hpp"
#include "../include/utilities.hpp"

HealthBar::HealthBar(int x, int y, int width, int height): 
               m_rect({x, y, width, height}), 
               m_renderer(Game::appWindow->renderer),
               m_currentTextureIndex(0)
{
	std::vector<std::string> imagePaths = {	"assets/images/players/health_bar/health_bar_1.png", 
											"assets/images/players/health_bar/health_bar_2.png", 
											"assets/images/players/health_bar/health_bar_3.png",
											"assets/images/players/health_bar/health_bar_4.png",
											"assets/images/players/health_bar/health_bar_5.png",
											"assets/images/players/health_bar/health_bar_6.png"};

    for (const auto &imagePath : imagePaths)
    {
        SDL_Surface *surface = load_png(imagePath.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_FreeSurface(surface);
        m_textures.push_back(texture);
    }
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
    SDL_RenderCopy(m_renderer, m_textures[m_currentTextureIndex], NULL, &m_rect);
}


void HealthBar::punched()
{
    
}