#include "UI/Game-Elements/TurnIndicator.hpp"

TurnIndicator::TurnIndicator(sf::Font &font) : text(font, "Turn:"), turnShow(font) {}

void TurnIndicator::setPosition(sf::Vector2f _position){
    position = _position;
}

void TurnIndicator::setSize(sf::Vector2f _size){
    size = _size;
}

void TurnIndicator::updateTurn(GameState &_gameState){
    if (_gameState.turn == GameState::Turn::black){
        turn = Turn::black;
    }
    else{
        turn = Turn::white;
    }
}

void TurnIndicator::draw(sf::RenderWindow &window){
    shape.setSize(size, radius);
    shape.setPosition(position);
    shape.setColor(sf::Color(40, 40, 40));
    shape.draw(window);

    text.setFillColor(sf::Color(64, 160, 200));
    text.setCharacterSize(size.y * text_scale);
    text.setPosition(position);
    alignText(text, 1.2f, text_align_v);
    window.draw(text);

    if (turn == Turn::black){
        turnShow.setString("Black");
        turnShow.setFillColor(sf::Color(160, 160, 160));
    }
    else{
        turnShow.setString("White");
        turnShow.setFillColor(sf::Color::White);
    }
    
    turnShow.setCharacterSize(size.y * text_scale);
    turnShow.setPosition(position);
    alignText(turnShow, -.025f, text_align_v);
    window.draw(turnShow);
}