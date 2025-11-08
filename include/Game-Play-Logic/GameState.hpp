#pragma once

#include <UI/Game-Elements/Stone.hpp>
#include <algorithm>
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
    
    void update();
}; 

