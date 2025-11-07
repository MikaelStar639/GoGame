#pragma once

#include <SFML/Graphics.hpp>
#include "Ultil.hpp"

class Board {
private:
    sf::RectangleShape boardShape;
    sf::RectangleShape horizontalLines;
    sf::RectangleShape verticalLines;
    sf::RectangleShape intersections;
    std::vector<sf::Text> labelnum;
    std::vector<sf::Text> labelchar;

public:
    sf::Vector2f size;
    sf::Vector2f position;

    float thickness;
    float gap;
    int gridNum;
    float Gridx[20];
    float Gridy[20];
    // constructor 
    Board(const sf::Font &font);
    // set position of the board
    void setPosition(sf::Vector2f _position);
    void draw(sf::RenderWindow &window);

};