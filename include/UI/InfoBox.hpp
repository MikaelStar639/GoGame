#pragma once
#include "UI/RoundRectShape.hpp"
#include <Ultil/Ultil.hpp>
#include <Game-Play-Logic/GameState.hpp>

class InfoBox{
private:
    sf::Text text;
    RoundRectShape shape;
    sf::Vector2f position;
    sf::Vector2f size = {300.f, 75.f};
    
    float text_scale   = 0.5f;
    float text_align_v = 0.6f;
    float radius       = 10.f;

public:
    sf::Text Info;
    InfoBox(sf::Font &font);
    void setPosition(sf::Vector2f _position);
    void setText(std::string str);
    void setState(std::string str);
    void setSize(sf::Vector2f _size);
    void draw(sf::RenderWindow &window);
};