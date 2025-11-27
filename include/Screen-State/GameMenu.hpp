#pragma once

#include "UI/Button.hpp"
#include "ScreenState.hpp"

class GameMenu{
private:
    Button newGameButton; 
    Button continueButton;
    Button saveGameButton;
    Button loadGameButton; 
    Button backButton;

    sf::Sprite &BackgroundSprite;

    sf::RenderWindow &window;

    void setBackground(sf::Sprite &backgroundSprite);
public:
    GameMenu(sf::Font &font, sf::RenderWindow &window, sf::Sprite &BackgroundSprite);

    screenState nextState = screenState::GameMenu;
    
    bool loadGame = false;
    bool saveGame = false;

    void updateButton(Mouse &mouse);
    void drawButton();
    void run();
};