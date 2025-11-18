#pragma once
#include "UI/RoundRectShape.hpp"
#include <Ultil.hpp>
#include <Game-Play-Logic/GameState.hpp>

class TurnIndicator{
public:
    enum class Turn{
        black,
        white
    };

    RoundRectShape shape;
    sf::Text text;
    sf::Text turnShow;

    Turn turn = Turn::white;
    TurnIndicator(sf::Font &font);

    sf::Vector2f position;
    sf::Vector2f size = {300.f, 75.f};
    
    float text_scale   = 0.5f;
    float text_align_v = 0.6f;
    float radius       = 10.f;

    void updateTurn(GameState &gameState);
    void setPosition(sf::Vector2f _position);
    void setSize(sf::Vector2f _size);
    void draw(sf::RenderWindow &window);
};