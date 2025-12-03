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
#include "AI/AI.hpp"

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
    void loadGame(std::string _address);
    void saveGame(std::string _address);
    
    //* Change Stone Style
    void ChangeStoneStyle(StoneStyle style);

    //* Reset
    void reset();

    //* Run 
    void run();

    //* AI
    bool isAIMode = false;
    
private:
    //Buttons
    Button backButton;
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
    
    //window
    sf::RenderWindow &window;

    //* Update
    void update(Mouse &mouse);
    void updateFeatureButton(Mouse &mouse);
    void updateGameButton(Mouse &mouse);
    void updateStone(Mouse &mouse);
    void updateIndicator();
    void updateScoreBoard();
    void updateScreenState();
    void updateGameState();
    void SyncStoneWithGameState();

    //* Render
    void render(Mouse &mouse);
    void setBackground();
    void drawBoard();
    void drawButton();
    void drawStone();
    void drawIndicator();
    void drawScoreBoard();

    //* Endgame
    EndGameWindow endGame;
    void drawEndGame(Mouse &mouse);

    //* Cordinate of the Stone on the Board
    Position to_cord(sf::Vector2f position);

    //* AI
    void updateAI();
    void updateAIMove();
    AI bot639;
};