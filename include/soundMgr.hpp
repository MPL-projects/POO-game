// filename : soundMgr.hpp
#ifndef SOUNDMGR_HPP
#define SOUNDMGR_HPP

// Include libraries
#include <map>
#include <string>
#include <iostream>
#include <SDL2/SDL_mixer.h>

// Preprocessed directives
#define FREQ 44100
#define CHUNK_SIZE 2048

/* Definition of the class : "SoundMgr" */

class SoundMgr 
{
	public:

		// Public methods

		virtual ~SoundMgr() = default;														// Virtual destructor

		virtual void playSound(const std::string& id) = 0;									// "playSound" pure virtual method :
		virtual void loadSound(const std::string& id, const std::string& filePath) = 0;		// "loadSound" pure virtual method :
		virtual void cleanSound() = 0;														// "cleanSound" pure virtual method :
};

#endif