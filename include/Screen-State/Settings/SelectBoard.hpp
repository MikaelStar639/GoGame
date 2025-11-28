#pragma once

#include "UI/Game-Elements/Board.hpp"
#include "UI/Button.hpp"
#include "Screen-State/ScreenState.hpp"
#include "SFML/Audio.hpp"
#include "Assets-Manager/TextureManager.hpp"

class SelectBoard{
private:
    Button backButton;
    Button LightWoodButton;
    Button DarkWoodButton;
    Button PlainWoodButton;

    Board &board;

    sf::Sprite backgroundSprite;

    sf::RenderWindow &window;
    
    const float space = 75.f;
    
    void setBackground();
    void updateButton(Mouse &mouse);
    void draw();

public:
    SelectBoard(sf::Font &font, sf::RenderWindow &window, 
        TextureManager& gameTexture, Board &board);
    
    screenState nextState = screenState::SelectBoard;
    void run();
};