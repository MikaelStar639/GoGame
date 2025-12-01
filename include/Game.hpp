#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stack>

#include <Screen-State/ScreenState.hpp>
#include <Screen-State/Homescreen.hpp>
#include <Screen-State/GameMenu.hpp>
#include <Screen-State/PlayOptions.hpp>
#include <Screen-State/GameScreen.hpp>
#include <Screen-State/Settings/Settings.hpp>
#include <Screen-State/Settings/SelectBoard.hpp>
#include <Screen-State/Settings/SelectStone.hpp>

#include <Assets-Manager/AssetsManager.hpp>
class Game{
private:

    sf::RenderWindow window;
    sf::Font         font;
    sf::Image        icon;
    
    TextureManager gameTexture;
    SoundManager   gameSound;
    
    Board board;
    
    Homescreen  homeScreen;
    GameMenu    gameMenu;
    PlayOptions playoptions;
    Settings    settings;
    GameScreen  gameScreen;
    SelectBoard selectBoard;
    SelectStone selectStone;

    std::stack<screenState> screenStateStack;

    void addState(screenState state);
    void handleScreen();

    template<class currentScreen>
    void updateScreen(currentScreen& screen);
    
public:
    Game();
    void run();
};