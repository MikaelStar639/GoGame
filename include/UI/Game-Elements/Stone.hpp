#pragma once
#include <SFML/Graphics.hpp>

class Stone{    

private:
    sf::Sprite BlackStoneSprite;
    sf::Sprite WhiteStoneSprite;
    sf::Texture whitestone;
    sf::Texture blackstone;

public:
    enum class stoneState{
        empty,
        black,
        white
    };

    enum class color{
        black,
        white
    };

    // board info
    stoneState state = stoneState::empty;
    Stone(sf::Vector2f _pos);
    void setPosition(sf::Vector2f pos);
    bool isContain(sf::Vector2f point);
    
    // visual info
    sf::Vector2f position;
    void setState(stoneState state);
    void draw(sf::RenderWindow &window, color col, bool isTransparent = false);
};