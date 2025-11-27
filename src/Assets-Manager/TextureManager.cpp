#include "Assets-Manager/TextureManager.hpp"

sf::Texture& TextureManager::operator[](const std::string& name) {
    if (!textures.count(name)){
        throw std::runtime_error("Failed to get texture: " + name);
    }
    return textures[name];
}

void TextureManager::load(const std::string& path, const std::string& name){
    if (!textures[name].loadFromFile(path)){
        throw std::runtime_error("Failed to get texture: " + path);
    }
}

TextureManager::TextureManager(){
    load("assets/images/Background.png", "BackGround");
    load("assets/images/BlackStone.png", "BlackStone");
    load("assets/images/WhiteStone.png", "WhiteStone");
    load("assets/images/PixelatedBlackStone.png", "PixelatedBlackStone");
    load("assets/images/PixelatedWhiteStone.png", "PixelatedWhiteStone");
    load("assets/images/DarkWood.png", "DarkWood");
    load("assets/images/LightWood.png", "LightWood");
    load("assets/images/PlainWood.png", "PlainWood");
}