#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Ultil.hpp"
#include <stack>

class Game{
public:
    enum class windowState{
        Homescreen,
        PlayOptions,
        Resume,
        Settings,
        SelectBoard,
        SelectStone,
        GameScreen,
        Exit
    };

    Game();

    std::stack<windowState> windowStateStack;

    sf::RenderWindow window;
    sf::Font         font;

    void run();
};