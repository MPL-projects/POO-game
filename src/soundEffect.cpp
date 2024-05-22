#include "../include/soundEffect.hpp"

// Play a sound effect by its ID
void SoundEffect::playSound(const std::string& id) {
    // Check if the sound ID exists in the sound map
    if (e_SoundMap.find(id) != e_SoundMap.end()) {
        // Play the sound effect on any available channel
        Mix_PlayChannel(-1, e_SoundMap[id], 0);
    } else {
        // Print an error message if the sound ID is not found
        std::cerr << "Sound ID not found: " << id << std::endl;
    }
}

// Load a sound effect from a file and associate it with an ID
void SoundEffect::loadSound(const std::string& id, const std::string& filePath) {
    // Load the sound effect from the specified file
    Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
    if (chunk != nullptr) {
        // Add the loaded sound effect to the sound map
        e_SoundMap[id] = chunk;
    } else {
        // Print an error message if the sound effect failed to load
        std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
    }
}

// Clean up all loaded sound effects
void SoundEffect::cleanSound() {
    // Iterate through the sound map and free each sound effect
    for (auto& pair : e_SoundMap) {
        Mix_FreeChunk(pair.second);
    }
    // Clear the sound map
    e_SoundMap.clear();
}

// Destructor for SoundEffect class
SoundEffect::~SoundEffect() {
    // Clean up all loaded sound effects
    cleanSound();
}

// Set the volume for all sound effects
void SoundEffect::setVolume(int volume) {
    // Clamp the volume to the valid range
    if (volume < 0) {
        volume = 0;
    } else if (volume > MIX_MAX_VOLUME) {
        volume = MIX_MAX_VOLUME;
    }
    currentVolume = volume; // Set the current volume
    // Set the volume for each loaded sound effect
    for (auto& pair : e_SoundMap) {
        Mix_VolumeChunk(pair.second, currentVolume);
    }
}
