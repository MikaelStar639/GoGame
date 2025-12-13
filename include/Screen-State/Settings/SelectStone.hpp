#pragma once

#include "UI/Button.hpp"
#include "Screen-State/ScreenState.hpp"
#include "Screen-State/GameScreen.hpp"
#include "Assets-Manager/TextureManager.hpp"
class SelectStone: public Screen{
private:
    Button backButton;
    Button ClassicButton;
    Button PixelButton;

    GameScreen &gamescreen;

    sf::Sprite backgroundSprite;

    sf::RenderWindow &window;
    
    const float space = 75.f;

    void setBackground();
    void updateButton(Mouse &mouse);
    void updateScreenState();
    void updateStyle();
    void draw();

public:
    enum class SelectStoneState{
        Classic,
        Pixel,
    };

    SelectStone(sf::Font &font, sf::RenderWindow &window, 
                GameScreen &_gamescreen, TextureManager &_gameTexture);
    
    void run();
};