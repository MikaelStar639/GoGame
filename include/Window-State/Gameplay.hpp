#pragma once

#include "Game.hpp"

#include "UI/Button.hpp"
#include "UI/Game-Elements/Board.hpp"
#include "UI/Game-Elements/Stone.hpp"

#include "Game-Play-Logic/GameState.hpp"


class Gameplay{
private:
    Button backButton;
    Button redoButton;
    Button undoButton;
    Button passButton;
    Button resignButton;

    sf::RenderWindow &window;

public:
    Gameplay(sf::Font &font, sf::RenderWindow &window);

    Game::windowState nextState = Game::windowState::GamePlay;

    void setBackground(sf::Sprite &backgroundSprite);
    void setBoard(sf::Sprite &boardSprite);
    void drawBoard();

    void updateButton(Mouse &mouse);
    void drawButton();
    
    void updateGameState();
    void updateStone();

    void drawStone();
    
    void run();
};