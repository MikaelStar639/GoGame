#pragma once

#include <SFML/Graphics.hpp>
#include <Ultil/Ultil.hpp>
#include <Assets-Manager/AssetsManager.hpp>

class Board {
private:    
    sf::Sprite boardSprite;
    TextureManager &textures;

    sf::RectangleShape horizontalLines;
    sf::RectangleShape verticalLines;
    sf::RectangleShape intersections;
    std::vector<sf::Text> labelnum;
    std::vector<sf::Text> labelchar;

public:
    enum class BoardStyle{
        DarkWood,
        LightWood,
        PlainWood,
    };
    
    sf::Vector2f size;
    sf::Vector2f position;

    float thickness;
    float gap;
    int gridNum;
    float gridX[20];
    float gridY[20];
    // constructor 
    Board(const sf::Font &font, TextureManager &_gameTexture);
    // set position of the board
    void setPosition(sf::Vector2f _position);
    void draw(sf::RenderWindow &window);
    // Setting Board Style
    void ChangeStyle(BoardStyle state);
};