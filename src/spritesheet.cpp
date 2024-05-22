#include "../include/spritesheet.hpp"
#include "../include/game.hpp"
#include <iostream>

// Constructor for Spritesheet class
Spritesheet::Spritesheet(char const *path, int nb_row, int nb_column) : renderer(Game::appWindow->renderer) {
    row = nb_row;          // Set the number of rows in the spritesheet
    column = nb_column;    // Set the number of columns in the spritesheet
    load_skin(path);       // Load the spritesheet image from the specified path
    flip = SDL_FLIP_NONE;  // Initialize flip to no flipping
}

// Destructor for Spritesheet class
Spritesheet::~Spritesheet() {
    SDL_DestroyTexture(m_spritesheet_image_texture);  // Destroy the texture
    m_spritesheet_image_texture = NULL;               // Set the texture pointer to NULL
}

// Select a specific sprite from the spritesheet
void Spritesheet::select_sprite(int x, int y) {
    m_clip.x = x * m_clip.w;  // Set the x position of the clip based on the column
    m_clip.y = y * m_clip.h;  // Set the y position of the clip based on the row
}

// Draw the selected sprite on the screen
void Spritesheet::draw_selected_sprite(SDL_Renderer *renderer, SDL_Rect *position) {
    SDL_RenderCopyEx(renderer, m_spritesheet_image_texture, &m_clip, position, 0, nullptr, flip);  // Render the selected sprite
    // SDL_BlitSurface(m_spritesheet_image, &m_clip, window_surface, position);  // Alternative rendering method (commented out)
}

// Load the spritesheet image from a file
void Spritesheet::load_skin(char const *path) {
    SDL_Surface *m_spritesheet_image = load_png(path);  // Load the image from the specified path
    m_spritesheet_image_texture = SDL_CreateTextureFromSurface(renderer, m_spritesheet_image);  // Create a texture from the surface
    height = m_spritesheet_image->h;  // Get the height of the image
    width = m_spritesheet_image->w;   // Get the width of the image
    m_clip.w = width / column;  // Calculate the width of a single sprite
    m_clip.h = height / row;    // Calculate the height of a single sprite
    SDL_FreeSurface(m_spritesheet_image);  // Free the surface
    m_spritesheet_image = NULL;            // Set the surface pointer to NULL
}
