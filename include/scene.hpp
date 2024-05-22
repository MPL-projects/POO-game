// Filename : scene.hpp

#ifndef SCENE_HPP
#define SCENE_HPP

// Include header files
#include "utilities.hpp"

// Include libraries
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>


using namespace std;

/* Definition of the class : "Scene" */

class Scene
{
	public:

		// Public methods 

		Scene(){};															// Constructor
		virtual ~Scene(){};													// Virtual Destructor

		void drawScene();													// "drawScene" method : Draw the scene
		void draw_boxes();													// "draw_boxes" method : Draw bounding boxes
		void load_scene(const std::string& jsonFilePath);					// "load_scene" method : Load a scene from a JSON file
		Param set_param(SDL_Rect pos, SDL_RendererFlip flip, int rotation);	// "set_param" method : Set parameters for a clip's position, flip, and rotation
		Clip set_clip(SDL_Rect clip, vector<Param> params);					// "set_clip" method : Set a clip with a rectangle and associated parameters
		Tiles set_tiles(SDL_Texture *asset, std::vector<Clip> clips);		// "set_tiles" method : Set tiles with a texture and associated clips

		std::vector<SDL_Rect>& get_boxes(){return boxes;};					// "get_boxes" accessor method : getter

	private:

		// Private Attributes

		std::vector<SDL_Rect> boxes;
		vector<Tiles> assests;
		
		static int id;
};

#endif