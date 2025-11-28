#pragma once

#include <SFML/Graphics.hpp>
#include <Ultil/Ultil.hpp>

class Board {
private:
    sf::Texture BlackBoard;
    sf::Texture LightBoard;
    sf::Texture PlainBoard;
    
    sf::Sprite DarkWoodSprite;
    sf::Sprite LightWoodSprite;
    sf::Sprite PlainWoodSprite;
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
    Board(const sf::Font &font);
    // set position of the board
    void setPosition(sf::Vector2f _position);
    void draw(sf::RenderWindow &window);
    // Setting Board Style
    void ChangeStyle(BoardStyle state);
};