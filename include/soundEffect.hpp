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

		void playSound(const std::string& id);								// "playSound" method : Play a sound effect by its ID
		void loadSound(const std::string& id, const std::string& filePath);	// "loadSound" method : Load a sound effect from a file and associate it with an ID
		void cleanSound();													// "cleanSound" method : Clean up all loaded sound effects
		void setVolume(int volume); 										// "setVolume" method : Set the volume for all sound effects

		// Public Attributes

		static EffectMap e_SoundMap;

	private:

		// Private attributes

		int currentVolume; 
};

#endif
