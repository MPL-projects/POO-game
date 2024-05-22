// Filename : utilities.hpp

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

// Include libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

// Function prototypes for utility functions
SDL_Surface *load_png(char const *path);
bool checkCollision2(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);

// Enumeration to represent directions
enum class Direction
{
    NONE,   // No direction
    UP,     // Up direction
    DOWN,   // Down direction
    LEFT,   // Left direction
    RIGHT   // Right direction
};

// Enumeration to represent game statuses
enum GameStatus {
    MAIN_MENU,      // Main menu status
    SKIN_MENU_1,    // Skin selection menu for player 1
    SKIN_MENU_2,    // Skin selection menu for player 2
    GAME,           // Game running status
    DEATH,          // Game over or death status
    SKIN1_LEFT,     // Skin selection for player 1 (left)
    SKIN1_RIGHT,    // Skin selection for player 1 (right)
    SKIN2_LEFT,     // Skin selection for player 2 (left)
    SKIN2_RIGHT,    // Skin selection for player 2 (right)
    INIT_PLAYERS,   // Initializing players status
    NONE            // No specific status
};

// Structure to hold parameters for rendering
typedef struct
{
    SDL_Rect pos;              // Position and size of the sprite
    SDL_RendererFlip flip;     // Flip mode for the sprite (horizontal/vertical)
    int rotation;              // Rotation angle for the sprite
} Param;

// Structure to hold a clip (portion) of a spritesheet
typedef struct
{
    SDL_Rect clip;                 // Rectangle defining the clip region
    std::vector<Param> params;     // Parameters for rendering the clip
} Clip;

// Structure to hold tiles, which consist of an asset (texture) and associated clips
typedef struct
{
    SDL_Texture *asset;            // Texture of the tile
    std::vector<Clip> clips;       // Clips associated with the texture
} Tiles;

#endif