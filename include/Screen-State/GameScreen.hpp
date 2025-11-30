#pragma once

#include "UI/Button.hpp"
#include "UI/Blur.hpp"
#include "UI/Game-Elements/Board.hpp"
#include "UI/Game-Elements/Stone.hpp"
#include "UI/Game-Elements/TurnIndicator.hpp"
#include "UI/Game-Elements/ScoreBoard.hpp"

#include "Screen-State/ScreenState.hpp"
#include "Screen-State/EndGame.hpp"
#include "Game-Play-Logic/GameState.hpp"
#include "Assets-Manager/AssetsManager.hpp"

#include <cmath>
#include <vector>

class GameScreen{
public:
    enum class StoneStyle{
        Classic,
        Cartoon
    };

    GameScreen(sf::Font &_font, sf::RenderWindow &_window,
                TextureManager &gameTexture, 
                SoundManager &gameSound,
                Board &_board);

    screenState nextState = screenState::GameScreen;
    
    //* Load/save Game
    bool canNotLoad = true;
    void loadGame(std::string _address);
    void saveGame(std::string _address);
    
    //* Change Stone Style
    void ChangeStoneStyle(StoneStyle style);

    //* Reset
    void reset();

    //* Run 
    void run();
    
    
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
    sf::Sprite backgroundSprite;
    TextureManager &textures;
    
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
    Position to_cord(sf::Vector2f position);

    //EndGame
    EndGameWindow endGame;


    //* UI
    void setBackground();
    void updateFeatureButton(Mouse &mouse);
    void updateGameButton(Mouse &mouse);
    void updateStone(Mouse &mouse);
    void updateIndicator();
    void updateScoreBoard();

    //* ScreenState
    void updateScreenState();

    //* Game State
    void updateGameState();
    void SyncStoneWithGameState();
};