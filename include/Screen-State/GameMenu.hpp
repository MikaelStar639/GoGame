#pragma once

#include "UI/Button.hpp"
#include "Screen-State/ScreenState.hpp"
#include "Assets-Manager/TextureManager.hpp"

class GameMenu{
private:
    Button newGameButton; 
    Button continueButton;
    Button saveGameButton;
    Button loadGameButton; 
    Button backButton;

    sf::Sprite backgroundSprite;

    sf::RenderWindow &window;

    void updateButton(Mouse &mouse);
    void updateScreenState();

    void drawButton();
    void setBackground();
    
public:
    GameMenu(sf::Font &font, sf::RenderWindow &window, TextureManager &gameTexture);
    screenState nextState = screenState::GameMenu;
    bool loadGame = false;
    bool saveGame = false;
    void run();
};