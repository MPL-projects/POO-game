#include "../include/soundEffect.hpp"

void SoundEffect::playSound(const std::string& id) {
    if (e_SoundMap.find(id) != e_SoundMap.end()) {
        Mix_PlayChannel(-1, e_SoundMap[id], 0);
    } else {
        std::cerr << "Sound ID not found: " << id << std::endl;
    }
}

void SoundEffect::loadSound(const std::string& id, const std::string& filePath) {
    Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
    if (chunk != nullptr) {
        e_SoundMap[id] = chunk;
    } else {
        std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
    }
}

void SoundEffect::cleanSound(){
    for (auto& pair : e_SoundMap) {
        Mix_FreeChunk(pair.second);
    }
    e_SoundMap.clear();
}

