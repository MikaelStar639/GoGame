#include "UI/Slider/Thumb.hpp"

Thumb::Thumb() {}

Thumb::Thumb(float _minX, float _y, float _length) : 
    length(_length),
    space(_length/maxValue), 
    minX(_minX), maxX(_minX + _length), 
    x(_minX + value * space), y(_y)
{
    thumbShape = RoundRectShape({10.f, 50.f}, 5.f, {x, _y}, sf::Color::White);
    bound      = sf::RectangleShape({_length + 12.f, 50.f});
    bound.setPosition({minX - 6.f, y - 25.f});
}

void Thumb::setPosition(sf::Vector2f _position){
    minX = _position.x;
    y = _position.y;
}

void Thumb::setLength(float _length){
    length = _length;
    space = _length/maxValue;
    maxX = minX + _length;
    x = minX + value * space;
    thumbShape = RoundRectShape({10.f, 50.f}, 5.f, {x, y}, sf::Color::White);
    bound      = sf::RectangleShape({_length + 12.f, 50.f});
    bound.setPosition({minX - 6.f, y - 25.f});
}

void Thumb::update(Mouse &mouse){
    if (mouse.isPressed && isPressed){
        float mouseX = mouse.position.x;
        if (minX <= mouseX && mouseX <= maxX){
            value = std::round((mouseX - minX)/space);
        }
        if (mouseX > maxX) value = maxValue;
        if (mouseX < minX) value = 0;
        return;
    }

    if (bound.getGlobalBounds().contains(mouse.position)){
        if (mouse.onPress){
            isPressed = true;

            float mouseX = mouse.position.x;
            if (mouseX < minX) mouseX = minX;
            if (mouseX > maxX) mouseX = maxX;
            value = std::round((mouseX - minX)/space);
        }

        if (mouse.isPressed && isPressed){
            isPressed = true;
        }

        isOver = true;
    }
    else{
        isOver    = false;
        isPressed = false;
    }
    
    if (!mouse.isPressed){
        isPressed = false;
    }
}

void Thumb::draw(sf::RenderWindow &window){
    x = minX + value * space;
    thumbShape.setPosition({x, y});
    thumbShape.draw(window);
}