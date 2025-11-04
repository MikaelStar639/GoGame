#pragma once
#include <SFML/Graphics.hpp>
#include "Ultil.hpp"

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

    gameState state;

    sf::RenderWindow window;
    sf::Font         font;

    void run();
};