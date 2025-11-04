#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Input/Mouse.hpp"
#include <Ultil.hpp>
#include "UI/RoundRectShape.hpp"
#include <array>
#include <string>

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
    bool isOver          = false;
    bool isPressed       = false;
    bool onPress         = false;
    bool onRelease       = false;

    sf::Color default_shape = sf::Color(0, 170, 255);
    sf::Color default_text  = sf::Color::White;
    sf::Color over_shape    = default_text;
    sf::Color over_text     = default_shape;
    sf::Color pressed_shape = sf::Color(64, 64, 127);
    sf::Color pressed_text  = sf::Color::White;

    Button(const sf::Font &font, sf::Vector2f _size, sf::Vector2f _position, float _radius);
    Button(const sf::Font &font);

    void update(Mouse &mouse);
    void draw(sf::RenderWindow& window);
    void setColor(std::array<sf::Color, 6> colorList);
    void setString(std::string _string);
    void setSize(sf::Vector2f _size);
    void setPosition(sf::Vector2f _position);
};
