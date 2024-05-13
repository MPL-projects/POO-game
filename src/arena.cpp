#include "../include/arena.hpp"
#include "../include/window.hpp"

#include <iostream>



Arena::Arena(SDL_Renderer *renderer) : Scene()
{
    screen_width = Window::WIDTH;
    screen_height = Window::HEIGHT;
    floor = new Scenesheet("assets/images/backgrounds_elements/floors/TilesetFloor.png",renderer);
    tree = new Scenesheet("assets/images/backgrounds_elements/TilesetNature.png",renderer);
    abandonedHouse = new Scenesheet("assets/images/backgrounds_elements/TilesetVillageAbandoned.png",renderer);
    water = new Scenesheet("assets/images/backgrounds_elements/TilesetWater1.png",renderer);

}

Arena::~Arena(){
    delete floor;
    delete tree;
    delete abandonedHouse;
    delete water;
}

void Arena::drawScene(SDL_Renderer *renderer){
    drawFloor(renderer);
    drawWater(renderer);
    drawAbandonedHouse(renderer);
    drawTree(renderer);
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
            position = {offsetX, offsetY, floor_w, floor_h};
            floor->draw_selected_sprite(renderer, &position);
            offsetX += floor_w;
        }
        offsetX = 0;
        offsetY += floor_h;
    }
}



void Arena::drawTree(SDL_Renderer *renderer){
    int ratio  = 3;
    tree->select_sprite(0,31,64,49);
    SDL_Rect position;

    /*Left tree*/

    int offsetY = 350;
    int offsetX = -20;
    for (int i = 0 ; i < 5; i++){
        if(i%3 == 1){
            offsetX = -15;
        }else if (i%3 == 2){
            offsetX = -10;
        }
        position  = {offsetX, offsetY, 64*ratio, 49*ratio};
        tree->draw_selected_sprite(renderer, &position);
        offsetY += 70;
        offsetX = -30;
    }

    offsetY = 520;
    offsetX = 110;
    for (int i = 0 ; i < 3; i++){
        if(i%3 == 1){
            offsetX += -15 ;
        }else if (i%3 == 2){
            offsetX += 10;
        }
        position  = {offsetX, offsetY, 64*ratio, 49*ratio};
        tree->draw_selected_sprite(renderer, &position);
        offsetY += 70;
        offsetX = 110;
    }

    position  = {200, 650, 64*ratio, 49*ratio};
    tree->draw_selected_sprite(renderer, &position);

    /*Right tree*/

    offsetY = 450;
    offsetX = screen_width - 172;
    for (int i = 0 ; i < 4; i++){
        if(i%3 == 1){
            offsetX += 15;
        }else if (i%3 == 2){
            offsetX += 10;
        }
        position  = {offsetX, offsetY, 64*ratio, 49*ratio};
        tree->draw_selected_sprite(renderer, &position);
        offsetY += 70;
        offsetX = screen_width - 172;
    }


    offsetY = 580;
    offsetX = screen_width - 280;
    for (int i = 0 ; i < 2; i++){
        if(i%3 == 1){
            offsetX -= 15;
        }else if (i%3 == 2){
            offsetX -= 10;
        }
        position  = {offsetX, offsetY, 64*ratio, 49*ratio};
        tree->draw_selected_sprite(renderer, &position);
        offsetY += 70;
        offsetX = screen_width - 290;
    }

    position  = {screen_width - 390, 650, 64*ratio, 49*ratio};
    tree->draw_selected_sprite(renderer, &position);

    int ratio_flower = 2;
    tree->select_sprite(1,176,14,16); //flower 1
    position  = {(15*screen_width)/40, (15*screen_height)/40, 14*ratio_flower, 16*ratio_flower};
    tree->draw_selected_sprite(renderer, &position);
    position  = {(22*screen_width)/40, (7*screen_height)/40, 14*ratio_flower, 16*ratio_flower};
    tree->draw_selected_sprite(renderer, &position);
    position  = {(19*screen_width)/40, (27*screen_height)/40, 14*ratio_flower, 16*ratio_flower};
    tree->draw_selected_sprite(renderer, &position);


    tree->select_sprite(49,176,14,16); //flower 2
    position  = {(8*screen_width)/40, (24*screen_height)/40, 14*ratio_flower, 16*ratio_flower};
    tree->draw_selected_sprite(renderer, &position);
    position  = {(29*screen_width)/40, (18*screen_height)/40, 14*ratio_flower, 16*ratio_flower};
    tree->draw_selected_sprite(renderer, &position);

    tree->select_sprite(96,176,16,16); //flower 3
    position  = {(36*screen_width)/40, (19*screen_height)/40, 16*ratio_flower, 16*ratio_flower};
    tree->draw_selected_sprite(renderer, &position);
    position  = {(20*screen_width)/40, (20*screen_height)/40, 16*ratio_flower, 16*ratio_flower};
    tree->draw_selected_sprite(renderer, &position);

    tree->select_sprite(64,176,16,16); //flower 4
    position  = {(4*screen_width)/40, (14*screen_height)/40, 16*ratio_flower, 16*ratio_flower};
    tree->draw_selected_sprite(renderer, &position);
    position  = {(29*screen_width)/40, (30*screen_height)/40, 16*ratio_flower, 16*ratio_flower};
    tree->draw_selected_sprite(renderer, &position);
    position  = {(21*screen_width)/40, (13*screen_height)/40, 16*ratio_flower, 16*ratio_flower};
    tree->draw_selected_sprite(renderer, &position);

    //384 336
    // tree->select_sprite(1,176,14,16); //flower 1
    // tree->select_sprite(49,176,14,16); //flower 2
    // tree->select_sprite(96,176,16,16); //flower 3
    // tree->select_sprite(64,176,16,16); //flower 4
    // position  = {0, 0, 500, 500};
    // tree->draw_selected_sprite(renderer, &position);

}


void Arena::drawAbandonedHouse(SDL_Renderer *renderer){
    SDL_Rect position ;
    int ratio = 3;
    int offsetX = 0 ;

    /*Draw floor*/

    abandonedHouse->select_sprite((96+32),50,32,30); //seconde stone
    for(int i = 0 ; i < 15; i++){
        position  = {offsetX,0,32*ratio,30*ratio};
        if(i%3 == 0){
            abandonedHouse->set_filp(SDL_FLIP_VERTICAL);
        }else if (i%3 == 1){
            abandonedHouse->set_filp(SDL_FLIP_NONE);
        }else {
            abandonedHouse->set_filp(SDL_FLIP_HORIZONTAL);
        }
        abandonedHouse->draw_selected_sprite(renderer, &position);
        offsetX += 32*ratio;
    }  

    offsetX = 0;
    abandonedHouse->select_sprite(96,50,32,30); //first stone
    for(int i = 0 ; i < 15; i++){
        position  = {offsetX,90,32*ratio,30*ratio};
        if(i%3 == 0){
            abandonedHouse->set_filp(SDL_FLIP_VERTICAL);
        }else if (i%3 == 1){
            abandonedHouse->set_filp(SDL_FLIP_NONE);
        }else {
            abandonedHouse->set_filp(SDL_FLIP_HORIZONTAL);
        }
        abandonedHouse->draw_selected_sprite(renderer, &position);
        offsetX += 32*ratio;
    }  

    /*floor corner on the left*/

    abandonedHouse->select_sprite((96+32),50,32,30); //seconde stone
    position  = {0,180,32*ratio,30*ratio};
    abandonedHouse->set_filp(SDL_FLIP_NONE);
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(96,50,32,30); //first stone
    position  = {96,180,32*ratio,30*ratio};
    abandonedHouse->set_filp(SDL_FLIP_VERTICAL);
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite((96+32),50,32,30); //seconde stone
    position  = {192,180,32*ratio,30*ratio};
    abandonedHouse->set_filp(SDL_FLIP_HORIZONTAL);
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(96,50,32,30); //first stone
    position  = {0,270,32*ratio,30*ratio};
    abandonedHouse->set_filp(SDL_FLIP_NONE);
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(113,65,15,15); //first little stone
    position  = {0,360,15*ratio,15*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    position  = {288,180,15*ratio,15*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    position  = {96,270,15*ratio,15*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

    /*floor corner on the right*/
    abandonedHouse->select_sprite((96+32),50,32,30); //seconde stone
    position  = {screen_width-96,180,32*ratio,30*ratio};
    abandonedHouse->set_filp(SDL_FLIP_NONE);
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(96,50,32,30); //first stone
    position  = {screen_width-96,270,32*ratio,30*ratio};
    abandonedHouse->set_filp(SDL_FLIP_VERTICAL);
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite((96+32),50,32,30); //seconde stone
    position  = {screen_width-96,360,32*ratio,30*ratio};
    abandonedHouse->set_filp(SDL_FLIP_HORIZONTAL);
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(96,50,32,30); //first stone
    position  = {screen_width-192,180,32*ratio,30*ratio};
    abandonedHouse->set_filp(SDL_FLIP_NONE);
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(113,65,15,15); //first little stone
    position  = {screen_width-243,180,15*ratio,15*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    position  = {screen_width-295,180,15*ratio,15*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    position  = {screen_width-147,270,15*ratio,15*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    position  = {screen_width-45,450,15*ratio,15*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

    /*Draw house*/


    abandonedHouse->select_sprite(0,0,64,50); //first hosue
    position  = {(1*screen_width)/12, 10, 64*ratio, 50*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(64,0,64,50); //seconde house
    position  = {(4*screen_width)/12, 0, 64*ratio, 50*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(64*2,0,48,50); //third house
    position  = {(7*screen_width)/12, 0, 48*ratio, 50*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite((64*2+48),0,48,50); //fourth house
    position  = {(9*screen_width)/12, 10, 48*ratio, 50*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

    /*decoration*/

    abandonedHouse->select_sprite(64,58,33,22); //little vase
    position  = {(((1*screen_width)/12)+110), 140, 33*ratio, 22*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);


    abandonedHouse->select_sprite(178,112,13,33); //sixth wood
    position  = {(((11*screen_width)/12)), 70, 13*ratio, 33*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    position  = {(((11*screen_width)/12)-13*ratio - 2), 70, 13*ratio, 33*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    position  = {(((11*screen_width)/12)+13*ratio + 2), 70, 13*ratio, 33*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    position  = {(((11*screen_width)/12)+13*ratio + 2), 70, 13*ratio, 33*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    abandonedHouse->set_rotation(90);
    position  = {(((11*screen_width)/12)), (50+33*ratio), 13*ratio, 33*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    abandonedHouse->set_rotation(0);

    abandonedHouse->select_sprite(97,95,14,33); //first wood
    position  = {(((6*screen_width)/12)+50), 20, 14*ratio, 33*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(97,128,14,16); //seconde wood
    position  = {(((6*screen_width)/12)), 60, 14*ratio, 16*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);


    abandonedHouse->select_sprite(97,144,14,33); //third wood
    position  = {(((3*screen_width)/12)+20), 20, 14*ratio, 33*ratio};
    abandonedHouse->set_rotation(70);
    abandonedHouse->draw_selected_sprite(renderer, &position);
    abandonedHouse->select_sprite(178,96,13,16); //fith wood
    position  = {(((3*screen_width)/12)+20), 90, 14*ratio, 16*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    abandonedHouse->set_rotation(0);

    abandonedHouse->select_sprite(97,128,14,16); //seconde wood
    position  = {10, 50, 14*ratio, 16*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);
    position  = {60, 30, 14*ratio, 16*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(146,113,30,29); //wheelbarrow
    position  = {20, 100, 30*ratio, 29*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(144,85,32,29); //frog
    position  = {20, 215, 32*ratio, 29*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(48,58,16,23); //white stone 1
    position  = {((8*screen_width)/12)+30, 640, 17*ratio, 25*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

    abandonedHouse->select_sprite(32,52,16,45); //white stone 2
    position  = {((3*screen_width)/12)+40, 580, 16*ratio, 44*ratio};
    abandonedHouse->draw_selected_sprite(renderer, &position);

   
    
    // abandonedHouse->select_sprite((96+(32*2)),48,16,30); //third stone
    // abandonedHouse->select_sprite(64,58,33,22); //little vase
    // abandonedHouse->select_sprite(97,95,14,33); //first wood
    // abandonedHouse->select_sprite(97,128,14,16); //seconde wood
    // abandonedHouse->select_sprite(97,144,14,33); //third wood
    // abandonedHouse->select_sprite(144,85,32,29); //frog
    // abandonedHouse->select_sprite(146,113,30,29); //wheelbarrow
    // abandonedHouse->select_sprite(178,96,13,16); //fith wood
    // abandonedHouse->select_sprite(178,112,13,33); //sixth wood
    // abandonedHouse->select_sprite(48,58,17,25); //white stone 1
    // abandonedHouse->select_sprite(32,52,16,44); //white stone 2
    // position  = {0, 0, 500, 500};
    // abandonedHouse->draw_selected_sprite(renderer, &position);

    // house->select_sprite(0,0,64,48);//first house
    // position  = {screen_width/2, 0, 180, 100};
    // house->draw_selected_sprite(renderer, &position);
}


void Arena::drawWater(SDL_Renderer *renderer){
    //448 272
    SDL_Rect position ;

    water->select_sprite(0,100,50,15); //water 1
    position  = {(3*screen_width)/12, 668, 750, 100};
    water->draw_selected_sprite(renderer, &position);

    // water->select_sprite(0,100,50,15); //water 1
    // position  = {0, 0, 500, 500};
    // water->draw_selected_sprite(renderer, &position);


}