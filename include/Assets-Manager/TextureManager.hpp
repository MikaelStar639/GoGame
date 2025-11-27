#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>

class TextureManager {
private:
    std::unordered_map<std::string, sf::Texture> textures;
    void load(const std::string& path, const std::string& name);
public:
    TextureManager();
    sf::Texture& operator[](const std::string& name);
};
