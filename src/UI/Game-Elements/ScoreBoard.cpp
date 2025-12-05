#include "UI/Game-Elements/ScoreBoard.hpp"

ScoreBoard::ScoreBoard(sf::Font &font, Player _player) : 
    text(font), score(font), player(_player) {}

void ScoreBoard::setScore(int num){
    if (player == Player::black){
        score.setString(std::to_string(num));
    }
    else{
        score.setString(std::to_string(num) + ".5");
    }
}

void ScoreBoard::setPosition(sf::Vector2f _position){
    position = _position;
}

void ScoreBoard::setSize(sf::Vector2f _size){
    size = _size;
}

void ScoreBoard::draw(sf::RenderWindow &window){
    shape.setSize(size, radius);
    shape.setPosition(position);
    shape.setColor(sf::Color(40, 40, 40));
    shape.draw(window);

    if (player == Player::black){
        text.setString("Black:");
        text.setFillColor(sf::Color(160, 160, 160));
    }
    else{
        text.setString("White:");
        text.setFillColor(sf::Color::White);
    }

    text.setCharacterSize(size.y * text_scale);
    text.setPosition(position);
    alignText(text, 1, text_align_v);
    window.draw(text);

    if (isWin){
        score.setFillColor(sf::Color(64, 200, 130));
    }
    else{
        score.setFillColor(sf::Color::Red);
    }

    score.setCharacterSize(size.y * text_scale);
    score.setPosition(position);
    if (player == Player::black){
        alignText(score, -.4f, text_align_v);
    }
    else{
        alignText(score, -.15f, text_align_v);
    }
    window.draw(score);
}