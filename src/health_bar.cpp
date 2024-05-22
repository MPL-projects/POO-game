#include "../include/health_bar.hpp"
#include "../include/game.hpp"
#include "../include/utilities.hpp"
#include "../include/player.hpp"

// Constructor for HealthBar class
HealthBar::HealthBar(int x, int y, int width, int height) : 
    m_rect({x, y, width, height}), 
    m_renderer(Game::appWindow->renderer) // Initialize renderer
{
    // List of image paths for the health bar textures
    std::vector<std::string> imagePaths = {
        "assets/images/players/health_bar/health_bar_empty.png", 
        "assets/images/players/health_bar/health_bar_content.png"
    };

    // Load textures from the image paths and store them in the m_textures vector
    for (const auto &imagePath : imagePaths)
    {
        SDL_Surface *surface = load_png(imagePath.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_FreeSurface(surface); 
        surface = nullptr;
        m_textures.push_back(texture);
    }

    // Initialize the life rectangle
    lifeRect = {m_rect.x + m_rect.w / 6, m_rect.y, m_rect.w - m_rect.w / 6, m_rect.h};
}

// Destructor for HealthBar class
HealthBar::~HealthBar()
{
    // Destroy all textures in the m_textures vector
    for (auto &texture : m_textures)
    {
        SDL_DestroyTexture(texture);
    }
    m_textures.clear(); // Clear the vector after destroying the textures
}

// Render the health bar on the screen
void HealthBar::render()
{
    SDL_RenderCopy(m_renderer, m_textures[1], nullptr, &lifeRect); // Render the life bar
    SDL_RenderCopy(m_renderer, m_textures[0], nullptr, &m_rect); // Render the health bar frame
}

// Update the life rectangle width based on the current life and maximum life
void HealthBar::actualDamages(int life, int max_life)
{
    float lifeRatio = (static_cast<float>(life) / static_cast<float>(max_life)) * static_cast<float>(m_rect.w - m_rect.w / 6);
    lifeRect.w = static_cast<int>(lifeRatio); // Update the width of the life rectangle
}
