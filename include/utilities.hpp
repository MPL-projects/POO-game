#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

SDL_Surface *load_bmp(char const *path);
bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);

#endif