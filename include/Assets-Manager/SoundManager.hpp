#pragma once

#include "SFML/Audio.hpp"
#include <unordered_map>
#include <vector>

class SoundManager{
private:
    std::vector<sf::SoundBuffer> buffers;
    std::vector<sf::Sound> sounds;
    std::unordered_map<std::string, int> id;
    void load(const std::string& path, const std::string& name);
public:
    SoundManager();
    sf::Sound& operator[](const std::string& name);
};
