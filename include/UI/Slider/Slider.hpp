#pragma once

#include <SFML/Graphics.hpp>
#include "Input/Mouse.hpp"

#include "UI/RoundRectShape.hpp"
#include "UI/Slider/Thumb.hpp"
#include "UI/Slider/Track.hpp"

#include <Ultil/Ultil.hpp>

class Slider{
private:
    RoundRectShape bound;
    Thumb          thumb;
    Track          track;
    sf::Text       text;

    sf::Vector2f size     = {75.f, 100.f};
    sf::Vector2f position = {0.f,  0.f};

    float text_scale   = 0.5f;
    float text_align_v = 0.6f;
    float radius       = 10.f;

public:
    float value; 

    Slider(sf::Font &font);
    
    void setPosition(sf::Vector2f _position);
    void setSize(sf::Vector2f _size);
    void setString(std::string str);
    
    void update(Mouse& mouse);
    void draw(sf::RenderWindow &window);

};