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

    //Sprite & Sound
    sf::Sprite BackgroundSprite;
    sf::Sound &stoneSound;
    
    //UI
    void drawBoard();
    void drawButton();
    void drawStone();
    
    //window
    sf::RenderWindow &window;

    //Cordinate of the Stone on the Board
    struct Cordinate{
        int y, x;
    };
    Cordinate to_cord(sf::Vector2f position);
    bool newTurn = false;

public:
    GameScreen(sf::Font &_font, sf::RenderWindow &_window, 
                sf::Texture &BlackTexture, sf::Texture &WhiteTexture,
                sf::Texture &BackgroundTexture, 
                sf::Sound &stoneSound,
                sf::Sound &stoneCaptureSound);

    Game::windowState nextState = Game::windowState::GameScreen;

    //* UI
    void setBackground(sf::Sprite &backgroundSprite);
    void setBoard(Board &board);
    void updateFeatureButton(Mouse &mouse);
    void updateGameButton(Mouse &mouse);
    void updateStone(Mouse &mouse);
    
    //* Game State
    void updateGameState();
    void SyncStoneWithGameState();
    
    //* Load/save Game
    bool canNotLoad = true;
    void loadGame(std::string _address);
    void saveGame(std::string _address);
    
    //* Run 
    void run();

    //* Copy to the other gameScreen
    void copyTo(GameScreen &gameScreen);
};