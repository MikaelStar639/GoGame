#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stack>

class Game{
public:
    enum class screenState{
        Homescreen,
        GameMenu,
        PlayOptions,
        Resume,
        NewGame,
        Settings,
        SelectBoard,
        SelectStone,
        GameScreen,
        Exit
    };

    Game();

    std::stack<screenState> screenStateStack;

    sf::RenderWindow window;
    sf::Font         font;

    void run();
};