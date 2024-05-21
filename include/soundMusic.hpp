// Filename : soundMusic.hpp

#ifndef SOUNDMUSIC_HPP
#define SOUNDMUSIC_HPP

// Include header files
#include "soundMgr.hpp"

// Include libraries
#include <string>
#include <iostream>
#include <SDL2/SDL_mixer.h>

using MusicMap = std::map<std::string, Mix_Music*>;


/* Definition of the class : "SoundMusic" inheriting from "SoundMgr" */

class SoundMusic : public SoundMgr 
{
	public:

		// Public methods

		SoundMusic() : currentVolume(MIX_MAX_VOLUME / 8) {};				// Constructor
		~SoundMusic();														// Destructor

		void playSound(const std::string& id);								// "playSound" method : 
		void loadSound(const std::string& id, const std::string& filePath);	// "loadSound" method : 		
		void cleanSound();													// "cleanSound" method :
		void stopSound();													// "stopSound" method :
		void printSoundMap();												// "printSoundMap" method : 

		void setVolume(int volume); 										// "setVolume" accessor method : setter


		// Public attributes

		static MusicMap m_SoundMap;

	private:

		// Private attributes

		int currentVolume; 
};

#endif
