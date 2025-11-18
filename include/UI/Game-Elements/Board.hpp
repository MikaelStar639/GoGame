#pragma once

#include <SFML/Graphics.hpp>
#include "Ultil.hpp"

class Board {
private:
    sf::Sprite DarkWoodSprite;
    sf::Sprite LightWoodSprite;
    sf::Sprite boardSprite;
    sf::RectangleShape horizontalLines;
    sf::RectangleShape verticalLines;
    sf::RectangleShape intersections;
    std::vector<sf::Text> labelnum;
    std::vector<sf::Text> labelchar;

public:
    enum class BoardStyle{
        DarkWood,
        LightWood,
    };
    sf::Vector2f size;
    sf::Vector2f position;

    float thickness;
    float gap;
    int gridNum;
    float gridX[20];
    float gridY[20];
    // constructor 
    Board(const sf::Font &font, sf::Texture &LightTexture, sf::Texture &DarkTexture);
    // set position of the board
    void setPosition(sf::Vector2f _position);
    void draw(sf::RenderWindow &window);
    // Setting Board Style
    void ChangeStyle(BoardStyle state);
};