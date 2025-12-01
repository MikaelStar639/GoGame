#pragma once

#include "Screen-State/ScreenState.hpp"
#include "UI/Button.hpp"
#include <Assets-Manager/AssetsManager.hpp>

class PlayOptions{
private:
    Button pvbButton; //player vs bot
    Button pvpButton; //player vs player
    Button backButton;

    sf::Sprite BackgroundSprite;

    sf::RenderWindow &window;

public:
    PlayOptions(sf::Font &font, sf::RenderWindow &window, TextureManager &textures);

    screenState nextState = screenState::PlayOptions;

    void setBackground(sf::Sprite &backgroundSprite);
    void updateButton(Mouse &mouse);
    void drawButton();
    void run();
};