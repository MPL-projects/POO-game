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

		void playSound(const std::string& id);								// "playSound" method : Play music by its ID
		void loadSound(const std::string& id, const std::string& filePath);	// "loadSound" method : Load music from a file and associate it with an ID	
		void cleanSound();													// "cleanSound" method : Clean up all loaded sounds
		void stopSound();													// "stopSound" method : Stop any currently playing music
		void printSoundMap();												// "printSoundMap" method : Print the contents of the sound map

		void setVolume(int volume); 										// "setVolume" accessor method : setter


		// Public attributes

		static MusicMap m_SoundMap;

	private:

		// Private attributes

		int currentVolume; 
};

#endif
