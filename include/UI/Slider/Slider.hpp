#pragma once

#include <SFML/Graphics.hpp>
#include "Input/Mouse.hpp"
#include "UI/RoundRectShape.hpp"

#include "UI/Slider/Thumb.hpp"
#include "UI/Slider/Track.hpp"

#include <Ultil.hpp>

class Slider{
private:
    RoundRectShape bound;
    Thumb          thumb;
    Track          track;
    sf::Text       text;

public:
    sf::Vector2f size     = {75.f, 100.f};
    sf::Vector2f position = {0.f,  0.f};
    
    float text_scale   = 0.5f;
    float text_align_v = 0.6f;
    float radius       = 10.f;

    float value; //0 -> 100

    Slider(sf::Font &font);
    Slider(std::string _str, sf::Font &font, sf::Vector2f _size, sf::Vector2f _position);
    
    void setPosition(sf::Vector2f _position);
    void setSize(sf::Vector2f _size);
    void setString(std::string str);
    
    void update(Mouse& mouse);
    void draw(sf::RenderWindow &window);

};