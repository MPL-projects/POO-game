#include "../include/button.hpp"
#include "../include/game.hpp"
#include "../include/utilities.hpp"

// Class constructor, initializes the button with given parameters and loads textures and font
Button::Button(int x, int y, int width, int height,
               const vector<string> &imagePaths, 
               const string &fontPath, 
               const string &name, 
               GameStatus a): 
               m_rect({x, y, width, height}), 
               m_renderer(Game::appWindow->renderer),
               m_currentTextureIndex(0), 
               m_isPressed(false)
{
    // Set the action for the button => GameStatus
    action = a;

    // Load button's textures from image paths
    for (const auto &imagePath : imagePaths)
    {
        SDL_Surface *surface = load_png(imagePath.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_FreeSurface(surface);
        m_textures.push_back(texture);
    }
    // Load the button's font from file
    m_font = TTF_OpenFont(fontPath.c_str(), 24);
    if (!m_font)
    {
        throw std::runtime_error("Failed to load font: " + fontPath);
    }

    SDL_Color textColor = {255, 255, 255}; // White text color

    // Create texture from text surface
    SDL_Surface *textSurface = TTF_RenderText_Solid(m_font, name.c_str(), textColor);
    m_textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    SDL_FreeSurface(textSurface);
}

// Class destructor, destroys all textures and font
Button::~Button()
{
    // Destroy all textures in the vector
    for (auto& texture : m_textures)
    {
        SDL_DestroyTexture(texture);
    }
    m_textures.clear(); // Clear the vector after destroying the textures
    SDL_DestroyTexture(m_textTexture);
    m_textTexture = NULL;
    TTF_CloseFont(m_font);
}

// Handle SDL events for the button
void Button::handleEvent(const SDL_Event &event)
{
    // Check for mouse motion event
    if (event.type == SDL_MOUSEMOTION)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Check if mouse is inside the button
        if (mouseX >= m_rect.x && mouseX <= m_rect.x + m_rect.w &&
            mouseY >= m_rect.y && mouseY <= m_rect.y + m_rect.h)
        {
            // Set texture index to 1 (hover state) if not pressed
            if(m_currentTextureIndex != 2){
                m_currentTextureIndex = 1;
            }
        }
        else
        {
            // Set texture index to 0 (normal state)
            m_currentTextureIndex = 0;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Check if mouse is inside the button
        if (mouseX >= m_rect.x && mouseX <= m_rect.x + m_rect.w &&
            mouseY >= m_rect.y && mouseY <= m_rect.y + m_rect.h)
        {
            // Set texture index to 2 (pressed state)
            m_currentTextureIndex = 2;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Check if mouse is inside the button
        if (mouseX >= m_rect.x && mouseX <= m_rect.x + m_rect.w &&
            mouseY >= m_rect.y && mouseY <= m_rect.y + m_rect.h)
        {
            // Set texture index to 1 (hover state)
            m_currentTextureIndex = 1;
            m_isPressed = !m_isPressed; // Toggle button pressed state


            // Play the sound effect when the button is pressed
            if (m_soundEffect && !m_soundId.empty()) {
                m_soundEffect->playSound(m_soundId);
            }

            // Set game status to the button's action
            Game::gameStatus = action;
        }
    }
}

// Render the button
void Button::render()
{
    // Copy the current texture to the renderer
    SDL_RenderCopy(m_renderer, m_textures[m_currentTextureIndex], NULL, &m_rect);

    // Calculate text position
    int textX, textY, textW, textH;
    SDL_QueryTexture(m_textTexture, NULL, NULL, &textW, &textH);
    if (m_currentTextureIndex == 2)
    {
        textY = m_rect.y + (m_rect.h - textH) / 2 + (m_rect.h / 8);
    }
    else
    {
        textY = m_rect.y + (m_rect.h - textH) / 2;
    }
    textX = m_rect.x + (m_rect.w - textW) / 2;
    SDL_Rect textRect = {textX, textY, textW, textH};

    // Copy the text texture to the renderer
    SDL_RenderCopy(m_renderer, m_textTexture, NULL, &textRect);
}

// Returns true if the button is currently pressed, false otherwise
bool Button::isPressed() const
{
    return m_isPressed;
    
}

// Sets the sound effect associated with the button
// soundEffect: A pointer to a SoundEffect object, which represents the sound effect to be played when the button is pressed
// soundId: A string representing the ID of the sound effect
void Button::setSoundEffect(SoundEffect* soundEffect, const std::string& soundId) {
    m_soundEffect = soundEffect;
    m_soundId = soundId;
}