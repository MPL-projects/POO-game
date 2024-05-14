#include "../include/utilities.hpp"
#include <iostream>

SDL_Surface *load_png(char const *path)
{
    SDL_Surface *image_surface = IMG_Load(path);

    if(!image_surface){
        std::cout << "Error: " << IMG_GetError() << std::endl;
        return 0;
    }
    return image_surface;
}

bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    for( int Abox = 0; Abox < (int)a.size(); Abox++ )
    {
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;

        for( int Bbox = 0; Bbox < (int)b.size(); Bbox++ )
        {
            leftB = b[ Bbox ].x;
            rightB = b[ Bbox ].x + b[ Bbox ].w;
            topB = b[ Bbox ].y;
            bottomB = b[ Bbox ].y + b[ Bbox ].h;

            if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                return true;
            }
        }
    }

    //If neither set of collision boxes touched
    return false;
}

bool checkCollision2(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b){
    //SDL_IntersectRect()
    

    for(auto& ra : a)
    {
        for(auto& rb : b)
        {
            if(SDL_HasIntersection(&ra, &rb))
            {
                return true;
            }
        }
    }

    //If neither set of collision boxes touched
    return false;
}
