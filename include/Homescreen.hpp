#pragma once

#include "Game.hpp"
#include "UI/Button.hpp"

class Homescreen{
private:
    Button playButton;
    Button resumeButton;
    Button settingButton;
    Button exitButton;

    sf::RenderWindow &window;

public:
    Homescreen(sf::Font &font, sf::RenderWindow &window);

    Game::gameState nextState = Game::gameState::Homescreen;

    void setBackground(sf::Sprite &backgroundSprite);
    void updateButton(Mouse &mouse);
    void drawButton();
    void run();
};