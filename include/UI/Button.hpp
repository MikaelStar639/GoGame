#pragma once

#include <SFML/Graphics.hpp>
#include "Input/Mouse.hpp"
#include "UI/RoundRectShape.hpp"
#include <Ultil.hpp>

#include <string>
#include <array>

class Button {
private:
    RoundRectShape shape;
    sf::Text       text;

public:
    sf::Vector2f size         = {200.f, 100.f};
    sf::Vector2f position     = {0.f,  0.f};
    std::string  string       = "Button";
    float        text_scale   = 0.5f;
    float        text_align_v = 0.6f;
    float        radius       = 10.f;

    //state
    bool isOver    = false;
    bool isPressed = false;
    bool onPress   = false;
    bool onRelease = false;

    sf::Color default_shape = sf::Color(40, 40, 40); 
    sf::Color default_text  = sf::Color(200, 200, 200); 

    sf::Color over_shape    = sf::Color(60, 60, 60); 
    sf::Color over_text     = sf::Color(200, 200, 200); 

    sf::Color pressed_shape = sf::Color(90, 90, 90);
    sf::Color pressed_text  = sf::Color(200, 200, 200);
    
    sf::Color invalid_shape = sf::Color(30, 30, 30);
    sf::Color invalid_text = sf::Color(150, 150, 150);

    bool isInvalid = false;

    Button(const sf::Font &font);

    void update(Mouse &mouse);
    void draw(sf::RenderWindow& window);
    void setColor(std::array<sf::Color, 6> colorList);
    void setString(std::string _string);
    void setSize(sf::Vector2f _size);
    void setPosition(sf::Vector2f _position);
};
