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

    Turn turn;
    int y_newStone, x_newStone;
    std::vector<std::pair<int, int>> capturedStones;

    HistoryState(Turn _turn, int y, int x,
                 const std::vector<std::pair<int, int>> &_capturedStones)
        :  turn(_turn), y_newStone(y), x_newStone(x), capturedStones(_capturedStones) {}
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
