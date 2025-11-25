#pragma once

#include <vector>
#include <string>
#include <fstream>

struct Position{
    int y = -1, x = -1;
};
class HistoryState {
public:
    enum class Turn{
        black,
        white
    };

    Turn turn = Turn::black;
    
    bool isPassed = false;
    Position newStone;
    std::vector<Position> capturedStones;

    HistoryState();
};


class History{
public:

    int index = -1;
    int undoCount = 0;

    std::vector<HistoryState> data;
    HistoryState& operator [] (int id);
    int size();

    void reset();
};
