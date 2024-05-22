#include "../include/utilities.hpp"
#include <iostream>

// Function to load a PNG image and return an SDL_Surface
SDL_Surface *load_png(char const *path) {
    SDL_Surface *image_surface = IMG_Load(path);  // Load the image from the specified path

    if (!image_surface) {  // Check if the image was loaded successfully
        std::cout << "Error: " << IMG_GetError() << std::endl;  // Print an error message if loading failed
        return nullptr;  // Return null if the image failed to load
    }
    return image_surface;  // Return the loaded image surface
}

// Function to check for collisions between two sets of SDL_Rects
bool checkCollision2(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b) {
    // Check if both sets of collision boxes have any rectangles
    if (a.size() > 0 && b.size() > 0) {
        for (auto &ra : a) {  // Iterate through each rectangle in the first set
            for (auto &rb : b) {  // Iterate through each rectangle in the second set
                if (SDL_HasIntersection(&ra, &rb)) {  // Check if there is an intersection between the two rectangles
                    return true;  // Return true if an intersection is found
                }
            }
        }
    }

    // Return false if no collisions were found
    return false;
}
