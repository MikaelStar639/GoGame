#pragma once

#include "UI/Button.hpp"
#include "Screen-State/ScreenState.hpp"
#include "Screen-State/GameScreen.hpp"
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

    GameScreen &gameScreen;

    void updateButton(Mouse &mouse);
    void updateScreenState();
    void updateGameScreen();

    void drawButton();
    void setBackground();
    
public:
    GameMenu(sf::Font &font, sf::RenderWindow &window, TextureManager &gameTexture, GameScreen &gameScreen);
    screenState nextState = screenState::GameMenu;
    void run();
};