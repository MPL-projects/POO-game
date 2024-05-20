#ifndef SOUNDMUSIC_HPP
#define SOUNDMUSIC_HPP

#include <string>
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "soundMgr.hpp"

using MusicMap = std::map<std::string, Mix_Music*>;

class SoundMusic : public SoundMgr {
public:
    SoundMusic() : currentVolume(MIX_MAX_VOLUME / 8) {}

    void playSound(const std::string& id) override;
    void loadSound(const std::string& id, const std::string& filePath) override;
    void cleanSound() override;
    void stopSound();
    void setVolume(int volume); 


    void printSoundMap();
    static MusicMap m_SoundMap;

private:
    int currentVolume; 
};

#endif // SOUNDMUSIC_HPP
