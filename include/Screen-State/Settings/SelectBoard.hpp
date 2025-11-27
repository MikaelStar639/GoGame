#pragma once

#include "UI/Game-Elements/Board.hpp"
#include "UI/Button.hpp"
#include "ScreenState.hpp"
#include "SFML/Audio.hpp"

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
    
    screenState nextState = screenState::SelectBoard;
    
    void setBackground(sf::Sprite &backgroundSprite);
    void updateButton(Mouse &mouse);
    void draw();
    void run();
};