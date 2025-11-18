#pragma once
#include "UI/RoundRectShape.hpp"
#include <Game-Play-Logic/GameState.hpp>
#include <Ultil.hpp>

class ScoreBoard{
public:
    enum class Player{
        black,
        white
    };

    RoundRectShape shape;
    sf::Text text;
    sf::Text score;

    Player player = Player::white;
    bool isWin = false;
    
    ScoreBoard(sf::Font &font, Player _player);

    sf::Vector2f position;
    sf::Vector2f size = {300.f, 75.f};
    
    float text_scale   = 0.5f;
    float text_align_v = 0.6f;
    float radius       = 10.f;

    void getScore(GameState &gameState);
    void setPosition(sf::Vector2f _position);
    void setSize(sf::Vector2f _size);
    void draw(sf::RenderWindow &window);
};