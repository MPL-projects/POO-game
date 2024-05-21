#include "../include/utilities.hpp"
#include <iostream>

SDL_Surface *load_png(char const *path)
{
    SDL_Surface *image_surface = IMG_Load(path);

    if (!image_surface)
    {
        std::cout << "Error: " << IMG_GetError() << std::endl;
        return 0;
    }
    return image_surface;
}

bool checkCollision2(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b)
{
    // SDL_IntersectRect()
    if (a.size() > 0 && b.size() > 0)
    {
        for (auto &ra : a)
        {
            for (auto &rb : b)
            {
                if (SDL_HasIntersection(&ra, &rb))
                {
                    return true;
                }
            }
        }
    }

    // If neither set of collision boxes touched
    return false;
}
