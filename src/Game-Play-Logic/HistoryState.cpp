#include "Game-Play-Logic/HistoryState.hpp"

HistoryState::HistoryState() {
    capturedStones.clear();
}

HistoryState& History::operator[](int id) {
    return data[id];
}

int History::size(){
    return data.size();
}

HistoryState History::last(){
    return data.back();
}

void History::reset(){
    index = -1;
    undoCount = 0;
    data.clear();
}