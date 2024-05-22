#include "../include/soundMusic.hpp"

// Play music by its ID
void SoundMusic::playSound(const std::string& id) {
    auto it = m_SoundMap.find(id);  // Find the music by its ID
    if (it == m_SoundMap.end()) {
        // Print an error message if the music ID is not found
        std::cerr << "Sound ID not found: " << id << std::endl;
        return;
    }
    Mix_Music* sound = it->second;  // Get the music from the map
    if (Mix_PlayMusic(sound, -1) == -1) {  // Play the music indefinitely (-1)
        // Print an error message if unable to play the music
        std::cerr << Mix_GetError() << ": " << id << std::endl;
    }
}

// Stop any currently playing music
void SoundMusic::stopSound() {
    Mix_HaltMusic();  // Stop the music
}

// Load music from a file and associate it with an ID
void SoundMusic::loadSound(const std::string& id, const std::string& filePath) {
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());  // Load the music file
    if (music != nullptr) {
        m_SoundMap[id] = music;  // Add the music to the sound map
    } else {
        // Print an error message if the music failed to load
        std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
    }
}

// Print the contents of the sound map
void SoundMusic::printSoundMap() {
    std::cout << "Sound Map Contents:" << std::endl;
    for (const auto& pair : m_SoundMap) {
        // Print each ID and its associated file path (pointer value for simplicity)
        std::cout << "ID: " << pair.first << ", File Path: " << pair.second << std::endl;
    }
}

// Destructor for SoundMusic class
SoundMusic::~SoundMusic() {
    cleanSound();  // Clean up all loaded sounds
}

// Clean up all loaded sounds
void SoundMusic::cleanSound() {
    for (auto& pair : m_SoundMap) {
        Mix_FreeMusic(pair.second);  // Free each music resource
    }
    m_SoundMap.clear();  // Clear the sound map
}

// Set the volume for the music
void SoundMusic::setVolume(int volume) {
    if (volume < 0) {
        volume = 0;  // Ensure volume is not below 0
    } else if (volume > MIX_MAX_VOLUME) {
        volume = MIX_MAX_VOLUME;  // Ensure volume does not exceed maximum
    }
    currentVolume = volume;  // Set the current volume
    Mix_VolumeMusic(currentVolume);  // Apply the volume to the music
}
