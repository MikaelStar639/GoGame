#pragma once

#include "SFML/Audio.hpp"
#include <unordered_map>
#include <vector>

class SoundManager{
private:
    std::vector<sf::SoundBuffer> buffers;
    std::unordered_map<std::string, int> id;
    std::vector<sf::Sound> sounds;
    
    void load(const std::string& path, const std::string& name);
    public:
    SoundManager();
    sf::Sound& operator[](const std::string& name);
  
    sf::Music backgroundMusic;
};
