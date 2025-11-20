#pragma once

#include "Game.hpp"
#include "UI/Button.hpp"

class GameMenu{
private:
    Button newGameButton; 
    Button continueButton;
    Button saveGameButton;
    Button loadGameButton; 
    Button backButton;

    sf::Sprite BackgroundSprite;

    sf::RenderWindow &window;

    void setBackground(sf::Sprite &backgroundSprite);
public:
    GameMenu(sf::Font &font, sf::RenderWindow &window, sf::Texture &BackgroundTexture);

    Game::windowState nextState = Game::windowState::GameMenu;
    
    bool loadGame = false;
    bool saveGame = false;

    void updateButton(Mouse &mouse);
    void drawButton();
    void run();
};