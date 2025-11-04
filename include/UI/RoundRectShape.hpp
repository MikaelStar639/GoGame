#pragma once
#include <SFML/Graphics.hpp>

class RoundRectShape {
private:
    sf::RectangleShape rect1;
    sf::RectangleShape rect2;
    sf::CircleShape    circle[4];

public:
    sf::Vector2f size;
    sf::Vector2f position;
    float radius;
    sf::Color color = sf::Color::Blue;

    // Constructor Declaration
    RoundRectShape();
    RoundRectShape(sf::Vector2f init_size, float init_radius, sf::Vector2f init_pos, sf::Color init_color);

    void setSize(sf::Vector2f _size, float _radius);
    void setPosition(sf::Vector2f _position);
    void setColor(sf::Color _color);
    void draw(sf::RenderWindow &window);
    
    // isContain declaration
    bool isContain(sf::Vector2f pos);
};