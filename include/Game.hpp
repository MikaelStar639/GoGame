#pragma once
#include <SFML/Graphics.hpp>
#include "Ultil.hpp"
#include <stack>

class Game{
public:
    enum class gameState{
        Homescreen,
        PlayOptions,
        Resume,
        Settings,
        GamePlay,
        Exit
    };

    Game();

    std::stack<gameState> gameStateStack;

    sf::RenderWindow window;
    sf::Font         font;

    void run();
};