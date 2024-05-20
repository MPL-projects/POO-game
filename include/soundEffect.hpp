#ifndef SOUNDEFFECT_HPP
#define SOUNDEFFECT_HPP

#include <string>
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "soundMgr.hpp"

using EffectMap = std::map<std::string, Mix_Chunk*>;


class SoundEffect : public SoundMgr {
public:
    SoundEffect(){};

    void playSound(const std::string& id);
    void loadSound(const std::string& id, const std::string& filePath);
    void cleanSound() override ;
    static EffectMap e_SoundMap;
};

#endif // SOUNDEFFECT_HPP
