#include "../include/arena.hpp"
#include <iostream>



Arena::Arena(SDL_Renderer *renderer, int w, int h)
{
    screen_width = w;
    screen_height = h;
    wall = new Arenasheet("assets/images/backgrounds_elements/walls/walls.png",renderer);
    floor = new Arenasheet("assets/images/backgrounds_elements/floors/TilesetFloor.png",renderer);
    house = new Arenasheet("assets/images/backgrounds_elements/TilesetHouse.png",renderer);
    tree = new Arenasheet("assets/images/backgrounds_elements/TilesetNature.png",renderer);
}

Arena::~Arena(){
    delete wall;
    delete floor;
    delete house;
    delete tree;
}

void Arena::drawArena(SDL_Renderer *renderer){
    drawFloor(renderer);
    drawHouse(renderer);
    drawTree(renderer);
    // drawWall(renderer);
}

void Arena::drawWall(SDL_Renderer *renderer){
    wall->select_sprite(16,57,45,50);
    int offsetX = 1;
    int offsetY_top = screen_height - 40;
    int offsetY_bottom = 1;
    int wall_w = (screen_width / 8);
    int wall_h = screen_height  / 6;
    SDL_Rect position_top, position_bottom;
    for (int i = 0; i<8; i++){
        position_top = {offsetX,offsetY_top, wall_w, wall_h};
        position_bottom = {offsetX,offsetY_bottom, wall_w, wall_h};   
        wall->draw_selected_sprite(renderer, &position_top);
        wall->draw_selected_sprite(renderer, &position_bottom);
        offsetX += wall_w ;
    }

}

void Arena::drawFloor(SDL_Renderer *renderer){
    floor->select_sprite(32,176,32,32);
    int offsetX = 0;
    int offsetY = 0;
    int floor_w = (screen_width / 6)+ 1;
    int floor_h = screen_height /6;
    SDL_Rect position;
    for (int i = 0; i<6; i++){
        for(int j = 0; j< 6; j++){
            if (i%3 == 0) {
                wall->set_filp(SDL_FLIP_HORIZONTAL);
            } else {
                wall->set_filp(SDL_FLIP_NONE);
            }
            position = {offsetX, offsetY, floor_w, floor_h};
            floor->draw_selected_sprite(renderer, &position);
            offsetX += floor_w;
        }
        offsetX = 0;
        offsetY += floor_h;
    }
    // floor->select_sprite(8,124,22,22);
    // floor->set_filp(SDL_FLIP_VERTICAL);
    // position = {0,0,100,100};
    // floor->draw_selected_sprite(renderer, &position);
    // floor_w = 80; floor_h = 80;
    // offsetX = 0; offsetY = 0;
    // for (int i = 0; i<2; i++){
    //     for(int j = 0; j< 18; j++){
    //         if (i%3 == 0) {
    //             wall->set_filp(SDL_FLIP_HORIZONTAL);
    //         } else {
    //             wall->set_filp(SDL_FLIP_NONE);
    //         }
    //         position = {offsetX, offsetY, floor_w, floor_h};
    //         floor->draw_selected_sprite(renderer, &position);
    //         offsetX += floor_w;
    //     }
    //     offsetX = 0;
    //     offsetY += floor_h;
    // }

    // floor->select_sprite(65,114,62,15);
    // floor->set_filp(SDL_FLIP_VERTICAL);
    // offsetX = 0; offsetY = 115;
    // for (int i=0; i<6; i++){
    //     position = {offsetX,offsetY,200,50};
    //     offsetX += 200*2;
    //     // floor->set_filp(SDL_FLIP_VERTICAL);
    //     floor->draw_selected_sprite(renderer, &position);
    // }

    // floor->select_sprite(67,125,61,14);
    // // floor->set_filp(SDL_FLIP_VERTICAL);
    // // position = {0,200,200*3,50*3};
    // // floor->draw_selected_sprite(renderer, &position);
    // offsetX = 200;
    // for (int i=0; i<6; i++){
    //     position = {offsetX,offsetY,200,50};
    //     offsetX += 200*2;
    //     floor->draw_selected_sprite(renderer, &position);
    // }
}

void Arena::drawHouse(SDL_Renderer *renderer){
    // house->select_sprite(192,100,10,10);
    // house->select_sprite(0,0,528,368); //tout
    house->select_sprite(400,225,63,79); //wood house
    SDL_Rect position  = {screen_width/2-50, 0, 120, 150};
    // house->set_filp(SDL_FLIP_VERTICAL);
    house->draw_selected_sprite(renderer, &position);

    // house->select_sprite(0,0,64,48);//first house
    // position  = {screen_width/2, 0, 180, 100};
    // house->draw_selected_sprite(renderer, &position);
}

void Arena::drawTree(SDL_Renderer *renderer){
    int ratio  = 2;
    tree->select_sprite(0,31,64,49);
    SDL_Rect position;
    
    //left bottom trees
    position  = {2, screen_height-160, 64*ratio, 49*ratio};
    tree->draw_selected_sprite(renderer, &position);

    position  = {100, screen_height-110, 64*ratio, 49*ratio};
    tree->draw_selected_sprite(renderer, &position);

    position  = {5, screen_height-100, 64*ratio, 49*ratio};
    tree->draw_selected_sprite(renderer, &position);

    //right bottom trees
    position  = {screen_width - 64*ratio -2, screen_height-160, 64*ratio, 49*ratio};
    tree->draw_selected_sprite(renderer, &position);

    position  = {screen_width - 64*ratio - 100, screen_height-110, 64*ratio, 49*ratio};
    tree->draw_selected_sprite(renderer, &position);

    position  = {screen_width - 64*ratio - 5, screen_height-100, 64*ratio, 49*ratio};
    tree->draw_selected_sprite(renderer, &position);

    // left top trees
    position  = {0, 0, 64*ratio, 49*ratio};
    tree->draw_selected_sprite(renderer, &position);

    position  = {60, 4, 64*ratio, 49*ratio};
    tree->draw_selected_sprite(renderer, &position);

    position  = {2, 40, 64*ratio, 49*ratio};
    tree->draw_selected_sprite(renderer, &position);

    

    


}