#ifndef SOUNDMGR_HPP
#define SOUNDMGR_HPP

#include <map>
#include <string>
#include <iostream>
#include <SDL2/SDL_mixer.h>

#define FREQ 44100
#define CHUNK_SIZE 2048


class SoundMgr {
public:
    virtual ~SoundMgr() = default;

    // Méthodes virtuelles pures pour les opérations de son
    virtual void playSound(const std::string& id) = 0;
    virtual void loadSound(const std::string& id, const std::string& filePath) = 0;
    virtual void cleanSound() = 0;
};

#endif // SOUNDMGR_HPP
