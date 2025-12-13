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

    GameState();

    int Size = 19;
    Turn turn = Turn::black;
    bool lastMovePass = false;
    bool lastMoveCaptured = false;
    bool newMove = false;
    Stone::State grid[19][19];
    
    //* End Game State
    bool isEnd = false;
    bool onEnd = false;
    
    //* Game func
    void addStoneMove(int y, int x);
    bool isIllegal(int y, int x);
    Score getScore();
    void reset();
    void pass();

    //*  redo and undo
    bool inUndo();
    void undo();
    void redo();

    //* load/save game
    bool isFileEmpty = true;
    bool isLoadGameValid(std::string _address);
    void load(std::string _address, bool &isAIMode, int &level);
    void save(std::string _address, bool isAIMode, int level);

    //* AI support
    std::vector<Position> getPossibleMove();
    int minimaxScore();

private:
    //* Game Elements
    History history;

    //* Game Management
    void addStone(int y, int x, Turn _turn);
    void deleteStone(int y, int x);
    bool canCapture();
    int  LibertiesCount(int y, int x);
    void RemoveCapturedStones(HistoryState &historyState);
    void swapTurn();
}; 

