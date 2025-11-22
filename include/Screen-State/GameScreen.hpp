#pragma once

#include "Game.hpp"

#include "UI/Button.hpp"
#include "UI/Blur.hpp"
#include "UI/Game-Elements/Board.hpp"
#include "UI/Game-Elements/Stone.hpp"
#include "UI/Game-Elements/TurnIndicator.hpp"
#include "UI/Game-Elements/ScoreBoard.hpp"

#include "Screen-State/EndGame.hpp"
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
    Button resetButton;

    //Game indicator & Score Board:
    TurnIndicator turnIndicator;
    ScoreBoard blackScoreBoard;
    ScoreBoard whiteScoreBoard;

    //Game Elements
    Board &board;
    GameState gameState;
    std::vector<std::vector<Stone>> grid;

    //Sprite & Sound
    sf::Sprite &BackgroundSprite;
    sf::Sprite &ClassicBlack;
    sf::Sprite &ClassicWhite;
    sf::Sprite &CartoonBlack;
    sf::Sprite &CartoonWhite;
    
    sf::Sound &endGameSound;    
    
    //UI
    void drawBoard();
    void drawButton();
    void drawStone();
    void drawIndicator();
    void drawScoreBoard();
    
    //window
    sf::RenderWindow &window;

    //Cordinate of the Stone on the Board
    struct Cordinate{
        int y, x;
    };
    Cordinate to_cord(sf::Vector2f position);
    bool newTurn = false;

    //EndGame
    EndGameWindow endGame;

public:

    enum class StoneStyle{
        Classic,
        Cartoon
    };
    GameScreen(sf::Font &_font, sf::RenderWindow &_window,
                sf::Sprite &ClassicBlackTexture, sf::Sprite &ClassicWhiteTexture,
                sf::Sprite &CartoonBlackTexture, sf::Sprite &CartoonWhiteTexture,
                sf::Sprite &BackgroundSprite, 
                Board &_board,
                sf::Sound &stoneSound,
                sf::Sound &stoneCaptureSound,
                sf::Sound &endGameSound);

    Game::screenState nextState = Game::screenState::GameScreen;

    //* UI
    void setBackground(sf::Sprite &backgroundSprite);
    void setBoard(Board &board);
    void updateFeatureButton(Mouse &mouse);
    void updateGameButton(Mouse &mouse, bool isEndGame);
    void updateStone(Mouse &mouse);
    void updateIndicator();
    void updateScoreBoard();
    void ChangeStoneStyle(StoneStyle style);
    
    //* Game State
    void updateGameState();
    void SyncStoneWithGameState();
    
    //* Load/save Game
    bool canNotLoad = true;
    void loadGame(std::string _address);
    void saveGame(std::string _address);
    
    //* Reset
    void reset();

    //* Run 
    void run();

    //* Copy to the other gameScreen
    void copyTo(GameScreen &gameScreen);
};