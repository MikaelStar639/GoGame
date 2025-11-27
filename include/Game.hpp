#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stack>

#include <ScreenState.hpp>
#include <Screen-State/Homescreen.hpp>
#include <Screen-State/GameMenu.hpp>
#include <Screen-State/GameScreen.hpp>
#include <Screen-State/Settings/Settings.hpp>
#include <Screen-State/Settings/SelectBoard.hpp>
#include <Screen-State/Settings/SelectStone.hpp>

#include <Assets-Manager/AssetsManager.hpp>
class Game{
private:
    sf::RenderWindow window;
    sf::Font         font;
    TextureManager gameTexture;
    SoundManager   gameSound;
    // Homescreen  homeScreen;
    // GameMenu    GameMenu;
    // Settings    settings;
    // SelectBoard selectBoard;
    // GameScreen  gameScreen;

    std::stack<screenState> screenStateStack;

    void handleScreen();

public:
    Game();
    void run();
};