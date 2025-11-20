#pragma once

#include <vector>
#include <string>
#include <fstream>

class HistoryState {
public:
    enum class Turn{
        black,
        white
    };

    Turn turn = Turn::black;
    int y_newStone = 0, x_newStone = 0;
    bool isPassed = false;
    std::vector<std::pair<int, int>> capturedStones;

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
