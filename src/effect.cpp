#include "../include/effect.hpp"
#include "../include/game.hpp"

// Constructor for the Effect class
Effect::Effect(const char *path_to_effect, float ratio_, SDL_Rect position, int x_off_, int y_off_) 
    : m_spritesheet(path_to_effect, 24, 8), ratio(ratio_)
{
    // Initialize the renderer from the Game class
    renderer = Game::appWindow->renderer;

    // Set the position and size of the effect
    m_position.x = position.x;
    m_position.y = position.y;
    m_position.w = position.w;
    m_position.h = position.w;

    // Initialize offset and position variables
    x_off = x_off_;
    y_off = y_off_;
    x = m_position.x;
    y = m_position.y;

    // Select the initial sprite from the spritesheet
    m_spritesheet.select_sprite(0, 14);
    m_spritesheet_column = 0;
    show = false;
}

// Destructor for the Effect class
Effect::~Effect(){

}

// Update function to manage the effect's animation
void Effect::update()
{
    int mult = 3, column_int = m_spritesheet_column / mult;

    // If the effect should be shown
    if (show)
    {
        // Update the position of the effect
        m_position.x = x;
        m_position.y = y;

        // Select the appropriate sprite frame from the spritesheet
        m_spritesheet.select_sprite(column_int, 23);

        // Increment the spritesheet column for animation
        m_spritesheet_column++;

        // Reset the animation if the end is reached
        if (m_spritesheet_column > mult * 9){
            m_spritesheet_column = 0;
            show = false;
        }
    }
    else
        // Reset the column if the effect is not shown
        m_spritesheet_column = 0;
}

// Draw function to render the effect
void Effect::draw()
{
    // Uncomment the following line to draw a rectangle around the effect (for debugging purposes)
    // SDL_RenderDrawRect(renderer, &m_position);

    // If the effect should be shown, draw the selected sprite
    if (show)
        m_spritesheet.draw_selected_sprite(renderer, &m_position);
}

// Move function to change the position of the effect
void Effect::move(double x1, double y1){
    x = x1 + x_off;
    y = y1 + y_off;
}
