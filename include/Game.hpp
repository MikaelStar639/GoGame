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



class Game{
private:
std::stack<screenState> screenStateStack;
sf::RenderWindow window;
sf::Font         font;


public:
    Game();


    void run();
};