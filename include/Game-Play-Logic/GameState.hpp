#pragma once

#include <UI/Game-Elements/Stone.hpp>
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

    Stone::State grid[19][19];
    Turn turn = Turn::black;

    void addStone(int y, int x);
    void deleteStone(int y, int x);

    // illegal move check
    bool isIllegal(int y, int x, GameState::Turn turn);
    bool canCapture(GameState::Turn turn);
    int LibertiesCount(int y, int x);
    
    void RemoveCapturedStones(std::vector<std::vector<Stone>> &stoneGrid);

    void update();
}; 

