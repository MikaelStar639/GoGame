#include "UI/Blur.hpp"

Blur::Blur() : shape({1200.f, 900.f}) {
    shape.setFillColor(sf::Color(0, 0, 0, 100));
}

void Blur::draw(sf::RenderWindow &window){
    window.draw(shape);
}