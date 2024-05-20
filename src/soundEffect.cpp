#include "../include/soundEffect.hpp"

void SoundEffect::playSound(const std::string& id){
        if (e_SoundMap.find(id) != e_SoundMap.end()) {
            Mix_PlayChannel(-1, e_SoundMap[id], 0);
        }
        std::cout << "Press Enter to stop the loop..." << std::endl;
        std::cin.get();

        Mix_HaltChannel(-1);  // Stop the sound
        Mix_FreeChunk(e_SoundMap[id]); // Free the sound chunk
    }

void SoundEffect::loadSound(const std::string& id, const std::string& filePath){
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

