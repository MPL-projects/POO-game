#include "../include/utilities.hpp"

SDL_Surface *load_bmp(char const *path)
{
    SDL_Surface *image_surface = IMG_Load(path);

    if(!image_surface)
        return 0;
    
    return image_surface;
}