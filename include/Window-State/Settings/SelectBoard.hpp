#pragma once

#include "Game.hpp"
#include "UI/Game-Elements/Board.hpp"
#include "UI/Button.hpp"

class SelectBoard{
private:
    Button backButton;
    Button LightWoodButton;
    Button DarkWoodButton;
    Button PlainWoodButton;

    Board &board;

    sf::Sprite &BackgroundSprite;
    sf::Sound &BackgroundMusic;

    sf::RenderWindow &window;
    
    const float space = 75.f;

public:
    SelectBoard(sf::Font &font, sf::RenderWindow &window, Board &board,
             sf::Sprite &BackgroundSprite,
             sf::Sound &BackgroundMusic);
    
    Game::screenState nextState = Game::screenState::SelectBoard;
    
    void setBackground(sf::Sprite &backgroundSprite);
    void updateButton(Mouse &mouse);
    void draw();
    void run();
};