#pragma once

#include <SFML/Graphics.hpp>

class Blur{
private:
    sf::RectangleShape shape;
public:
    Blur();
    void draw(sf::RenderWindow &window);
};