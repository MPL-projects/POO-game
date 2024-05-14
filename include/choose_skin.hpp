#ifndef CHOOSE_SKIN_HPP
#define CHOOSE_SKIN_HPP
#include <SDL2/SDL.h>
#include "scenesheet.hpp"
#include  "scene.hpp"

class ChooseSkin : public Scene
{
	public:

		ChooseSkin(SDL_Renderer *renderer);
		~ChooseSkin();

		void drawBackground(SDL_Renderer *renderer);
		void drawArrow(SDL_Renderer *renderer, char *orientation);
		

	
	protected:
	
		int screen_width, screen_height;

		SDL_Rect     m_position;

		Scenesheet  *arrow, *sprite, *Background;

		void drawSprite(SDL_Renderer *renderer);
};

#endif