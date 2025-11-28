#pragma once

#include "UI/Button.hpp"
#include "Screen-State/ScreenState.hpp"
#include "Screen-State/GameScreen.hpp"
#include "Assets-Manager/TextureManager.hpp"
class SelectStone{
private:
    Button backButton;
    Button ClassicButton;
    Button CartoonButton;

    GameScreen &gamescreen;

    sf::Sprite backgroundSprite;

    sf::RenderWindow &window;
    
    const float space = 75.f;

    void setBackground();
    void updateButton(Mouse &mouse);
    void draw();

public:
    enum class SelectStoneState{
        Classic,
        Cartoon,
    };

    SelectStone(sf::Font &font, sf::RenderWindow &window, 
                GameScreen &_gamescreen, TextureManager &_gameTexture);
    
    screenState nextState = screenState::SelectStone;
    void run();
};