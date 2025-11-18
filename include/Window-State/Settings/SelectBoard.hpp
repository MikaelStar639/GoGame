#pragma once

#include "Game.hpp"
#include "UI/Game-Elements/Board.hpp"
#include "UI/Button.hpp"

class SelectBoard{
private:
    Button backButton;
    Button LightWoodButton;
    Button DarkWoodButton;

    Board &board;

    sf::Sprite BackgroundSprite;
    sf::Sound &BackgroundMusic;

    sf::RenderWindow &window;
    
    const float space = 75.f;

public:
    enum class SelectBoardState{
        LightWood,
        DarkWood,
    };
    SelectBoard(sf::Font &font, sf::RenderWindow &window, Board &board,
             sf::Texture &BackgroundTexture,
             sf::Sound &BackgroundMusic);
    
    Game::windowState nextState = Game::windowState::SelectBoard;
    
    void setBackground(sf::Sprite &backgroundSprite);
    void updateButton(Mouse &mouse);
    void draw();
    void run();
};