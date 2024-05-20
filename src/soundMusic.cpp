#include "../include/soundMusic.hpp"

void SoundMusic::playSound(const std::string& id){
    std::cout << "ID: " << id << ", File Path: " << m_SoundMap[id] << std::endl;
    Mix_Music* sound = m_SoundMap[id];
    if(Mix_PlayMusic(sound, -1) == -1){
        std::cerr << Mix_GetError() << ": " << id << std::endl;
        Mix_FreeMusic(sound);
    }
    std::cout << "Press Enter to stop the loop..." << std::endl;
    std::cin.get();

    Mix_HaltMusic();  // Stop the sound
    Mix_FreeMusic(sound); // Free the sound chunk
}

void SoundMusic::loadSound(const std::string& id, const std::string& filePath){
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (music != nullptr) {
        m_SoundMap[id] = music;
    } else {
        std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
    }

}

void SoundMusic::printSoundMap() {
    std::cout << "Sound Map Contents:" << std::endl;
    for (const auto& pair : m_SoundMap) {
        std::cout << "ID: " << pair.first << ", File Path: " << pair.second << std::endl;
    }
}


void SoundMusic::cleanSound(){
    for (auto& pair : m_SoundMap) {
        Mix_FreeMusic(pair.second);
    }
    m_SoundMap.clear();
}

