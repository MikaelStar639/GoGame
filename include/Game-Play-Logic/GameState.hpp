#pragma once

#include <SFML/Audio.hpp>
#include <UI/Game-Elements/Stone.hpp>
#include <Game-Play-Logic/HistoryState.hpp>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>  
#include "random"

class GameState{
public:
    struct Score{
        int black;
        int white;
    };

    enum class Turn{
        black,
        white
    };

    GameState(sf::Sound &stoneCaptureSound, sf::Sound &stoneSound);

    Turn turn = Turn::black;
    void addStoneMove(int y, int x);
    void pass();
    bool lastMovePass = false;
    Stone::State grid[19][19];
    
    //* End Game State
    bool isEnd = false;
    Score getScore();
    void reset();
    bool isIllegal(int y, int x);
    
    //*  redo and undo
    void undo();
    void redo();

    //* load/save game
    bool isFileEmpty = true;
    void load(std::string _address);
    void save(std::string _address);

    //* AI support
    History virtualHistory;
    std::vector<Position> getPossibleMove();
    void addVirtualMove(int y, int x);
    void virtualUndo();
    int  minimaxScore();

private:
    sf::Sound &stoneCaptureSound;
    sf::Sound &stoneSound;

    //* Game Elements
    History history;

    //* Game Management
    void addStone(int y, int x, Turn _turn);
    void deleteStone(int y, int x);
    bool canCapture();
    int  LibertiesCount(int y, int x);
    void RemoveCapturedStones(HistoryState &historyState);
    void swapTurn();

    Score getScore2();
}; 

