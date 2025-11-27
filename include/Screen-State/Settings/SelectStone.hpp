#pragma once

#include "ScreenState.hpp"
#include "UI/Button.hpp"
#include "Screen-State/GameScreen.hpp"

class SelectStone{
private:
    Button backButton;
    Button ClassicButton;
    Button CartoonButton;

    GameScreen &gamescreen;

    sf::Sprite &BackgroundSprite;
    sf::Sound &BackgroundMusic;

    sf::RenderWindow &window;
    
    const float space = 75.f;

public:
    enum class SelectStoneState{
        Classic,
        Cartoon,
    };

    SelectStone(sf::Font &font, sf::RenderWindow &window, GameScreen &_gamescreen,
             sf::Sprite &BackgroundSprite,
             sf::Sound &BackgroundMusic);
    
    screenState nextState = screenState::SelectStone;
    
    void setBackground(sf::Sprite &backgroundSprite);
    void updateButton(Mouse &mouse);
    void draw();
    void run();
};