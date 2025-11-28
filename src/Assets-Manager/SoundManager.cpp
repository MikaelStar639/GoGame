#include "Assets-Manager/SoundManager.hpp"

sf::Sound& SoundManager::operator[](const std::string& name) {
    if (!id.count(name)){
        throw std::runtime_error("Failed to get Sound: " + name);
    }
    return sounds[id[name]];
}

void SoundManager::load(const std::string& path, const std::string& name){
    id[name] = sounds.size();

    buffers.push_back(sf::SoundBuffer());
    if (!buffers.back().loadFromFile(path)){
        throw std::runtime_error("Failed to get Buffer: " + path);
    }

    sf::Sound sound(buffers.back());
    sounds.push_back(sound);
}

SoundManager::SoundManager(){
    load("assets/sounds/stoneMove.mp3",    "StoneMove");
    load("assets/sounds/stoneCapture.mp3", "StoneCapture");
    load("assets/sounds/boom.mp3",         "Boom");

    if (!backgroundMusic.openFromFile("assets/sounds/BackgroundMusic.mp3")){
        throw std::runtime_error("Failed to get Music");
    }

    for (auto &sound: sounds){
        sound.setVolume(75);
    }
    
    backgroundMusic.setVolume(75);
    backgroundMusic.setLooping(true);
    backgroundMusic.play();
}