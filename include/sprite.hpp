#include <SDL2/SDL_image.h>
#include "../include/window.hpp"
#include <iostream>

using namespace std;

class Sprite {
public:
    SDL_Texture* texture;
    int x, y;
    int width, height;

    Sprite(SDL_Renderer* renderer, const char* imagePath, int startX, int startY) {
        // Charger l'image PNG
        SDL_Surface* surface = IMG_Load(imagePath);
        if (!surface) {
            // Gestion de l'erreur si le chargement de l'image échoue
            cerr << "Failed to load image: " << IMG_GetError() << endl;
            return;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
        x = startX;
        y = startY;
    }

    void draw(SDL_Renderer* renderer) {
        SDL_Rect dstRect = {x, y, width, height};
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }
};

int main() {
    Window window;
    window.createWindow("SDL Sprite Movement", 800, 600);

    SDL_Event event;
    bool quit = false;

    // Charger une texture pour le sprite
    Sprite sprite(window.renderer, "sprite.png", 0, 0); // Charger une image PNG

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Mise à jour de la position du sprite (par exemple, déplacement vers la droite)
        sprite.move(1, 0);

        // Effacer l'écran
        SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
        SDL_RenderClear(window.renderer);

        // Dessiner le sprite
        sprite.draw(window.renderer);

        // Rafraîchir l'écran
        SDL_RenderPresent(window.renderer);

        SDL_Delay(10); // Petit délai pour contrôler la vitesse du mouvement
    }

    window.destroyWindow();
    return 0;
}
