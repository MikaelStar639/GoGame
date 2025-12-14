#pragma once

#include <SFML/Graphics.hpp>
#include "Input/Mouse.hpp"
#include "UI/RoundRectShape.hpp"
#include <cmath>

class Thumb{
private:
    RoundRectShape thumbShape;
    sf::RectangleShape bound;

    float space;

public:
    int maxValue = 20;
    float length;
    float minX;
    float maxX;    
    float x, y;

    bool isOver    = false;
    bool isPressed = false;

    int value = 15;

    Thumb();
    Thumb(float minX, float y, float length);
    
    void setPosition(sf::Vector2f _position);
    void setLength(float length);
    void update(Mouse &mouse);
    void draw(sf::RenderWindow &window);
};