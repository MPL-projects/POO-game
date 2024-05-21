// Filename : soundEffect.hpp

#ifndef SOUNDEFFECT_HPP
#define SOUNDEFFECT_HPP

// Include header files
#include "soundMgr.hpp"

// Include libraries
#include <string>
#include <iostream>
#include <SDL2/SDL_mixer.h>


using EffectMap = std::map<std::string, Mix_Chunk*>;

/* Definition of the class : "SoundEffect" inheritating from "SoundMgr" */

class SoundEffect : public SoundMgr 
{
	public:

		// Public methods

		SoundEffect() : currentVolume(MIX_MAX_VOLUME / 8) {}				// Constructor
		~SoundEffect();														// Destructor

		void playSound(const std::string& id);								// "playSound" method : 
		void loadSound(const std::string& id, const std::string& filePath);	// "loadSound" method : 
		void cleanSound();													// "cleanSound" method : 
		void setVolume(int volume); 										// "setVolume" method : 

		// Public Attributes

		static EffectMap e_SoundMap;

	private:

		// Private attributes

		int currentVolume; 
};

#endif
