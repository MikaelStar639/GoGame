#pragma once

#include "Screen-State/ScreenState.hpp"
#include "Screen-State/GameScreen.hpp"
#include "UI/InfoBox.hpp"
#include "UI/Button.hpp"
#include <Assets-Manager/AssetsManager.hpp>

class PlayOptions{
private:
    Button pvbButton; //player vs bot
    Button pvpButton; //player vs player
    Button backButton;
    Button playButton;
    Button button9x9;
    Button button13x13;
    Button button19x19;
    Button selectLevelButton;
    sf::Text chooseModeText;
    sf::Text chooseSizeText;
    InfoBox difficultyBox;

    sf::Sprite backgroundSprite;

    sf::RenderWindow &window;
    GameScreen &gameScreen;

    void setBackground();
    void updateButton(Mouse &mouse);
    void drawButton();
    void updateScreenState();

public:
    PlayOptions(sf::Font &font, sf::RenderWindow &window, TextureManager &textures, GameScreen &gameScreen);
    screenState nextState = screenState::PlayOptions;
    void run();
};