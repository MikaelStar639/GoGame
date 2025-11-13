#pragma once

#include <UI/Game-Elements/Stone.hpp>
#include <Game-Play-Logic/HistoryState.hpp>
#include <algorithm>
#include <vector>
#include <queue>
#include <vector>

class GameState{
public:
    enum class Turn{
        black,
        white
    };

    GameState();

    Turn turn = Turn::black;
    Stone::State grid[19][19];
    std::vector<HistoryState> history;
    int HistoryIndex = -1;
    int undoCount = 0;
    bool lastMovePass = false;

    void addStone(int y, int x, Turn _turn);
    void deleteStone(int y, int x);

    // illegal move check
    bool isIllegal(int y, int x, GameState::Turn turn);
    bool canCapture(GameState::Turn turn);
    int LibertiesCount(int y, int x);

    // redo and undo
    void redo();
    void undo();
    
    void addStoneMove(int y, int x);
    void RemoveCapturedStones(HistoryState &historyState);

    void update();
}; 

