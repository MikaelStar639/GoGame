#pragma once
#include <SFML/Graphics.hpp>
#include "Ultil.hpp"

class Game{
private:
    enum class gameState{
        Homescreen,
        PlayOptions,
        GamePlay,
        Settings
    };

public:
    Game();

    gameState state;

    sf::RenderWindow window;
    sf::Font         font;


    void run();
};