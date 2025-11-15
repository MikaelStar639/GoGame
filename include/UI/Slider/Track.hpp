#pragma once

#include <SFML/Graphics.hpp>
#include <UI/Slider/Thumb.hpp>

class Track{
private:
    sf::RectangleShape leftShape;
    sf::RectangleShape rightShape;
public:
    float value; //0 -> 1
    float length;
    sf::Vector2f position;

    Track(Thumb &thumb);
    void setThumb(Thumb &thumb);
    void update(Thumb &thumb);
    void draw(sf::RenderWindow &window);
};