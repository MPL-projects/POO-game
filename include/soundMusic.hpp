#ifndef SOUNDMUSIC_HPP
#define SOUNDMUSIC_HPP

#include <string>
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "soundMgr.hpp"

using MusicMap = std::map<std::string, Mix_Music*>;

class SoundMusic : public SoundMgr {
public:
    SoundMusic() {};

    void playSound(const std::string& id) override;
    void loadSound(const std::string& id, const std::string& filePath) override;
    void cleanSound() override;
    void stopSound();


    void printSoundMap();
    static MusicMap m_SoundMap;
};

#endif // SOUNDMUSIC_HPP
