#pragma once

#include "Game.hpp"

#include "UI/Button.hpp"
#include "UI/Game-Elements/Board.hpp"
#include "UI/Game-Elements/Stone.hpp"

#include "Game-Play-Logic/GameState.hpp"
#include <cmath>
#include <vector>

class GameScreen{
private:
    //Feature Button
    Button backButton;

    //Game Button
    Button redoButton;
    Button undoButton;
    Button passButton;
    Button resignButton;

    //Game Elements
    Board board;
    GameState gameState;
    std::vector<std::vector<Stone>> grid;

    //window
    sf::RenderWindow &window;

    void drawBoard();
    void drawButton();
    void drawStone();

    //Cordinate of the Stone on the Board
    struct Cordinate{
        int y, x;
    };

    Cordinate to_cord(sf::Vector2f position);

    bool newTurn = false;

public:
    GameScreen(sf::Font &_font, sf::RenderWindow &_window, 
                sf::Texture &BlackTexture, sf::Texture &WhiteTexture);

    Game::windowState nextState = Game::windowState::GameScreen;

    void setBackground(sf::Sprite &backgroundSprite);
    void setBoard(Board &board);

    void updateFeatureButton(Mouse &mouse);
    void updateGameButton(Mouse &mouse);
    void updateStone(Mouse &mouse);
    
    void updateGameState();
    
    void run();
};