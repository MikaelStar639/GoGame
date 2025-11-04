#pragma once
#include <SFML/Graphics.hpp>
#include "Ultil.hpp"
#include <stack>

class Game{
public:
    enum class windowState{
        Homescreen,
        PlayOptions,
        Resume,
        Settings,
        GamePlay,
        Exit
    };

    Game();

    std::stack<windowState> windowStateStack;

    sf::RenderWindow window;
    sf::Font         font;

    void run();
};