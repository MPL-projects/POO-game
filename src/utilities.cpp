#include "../include/utilities.hpp"
#include <iostream>

SDL_Surface *load_bmp(char const *path)
{
    SDL_Surface *image_surface = IMG_Load(path);

    if(!image_surface){
        std::cout << "Error: " << IMG_GetError() << std::endl;
        return 0;
    }
    return image_surface;
}