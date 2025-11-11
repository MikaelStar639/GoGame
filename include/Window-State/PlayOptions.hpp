#pragma once

#include "Game.hpp"
#include "UI/Button.hpp"

class PlayOptions{
private:
    Button pvbButton; //player vs bot
    Button pvpButton; //player vs player
    Button backButton;

    sf::Sprite BackgroundSprite;

    sf::RenderWindow &window;

public:
    PlayOptions(sf::Font &font, sf::RenderWindow &window, sf::Texture &BackgroundTexture);

    Game::windowState nextState = Game::windowState::PlayOptions;

    void setBackground(sf::Sprite &backgroundSprite);
    void updateButton(Mouse &mouse);
    void drawButton();
    void run();
};