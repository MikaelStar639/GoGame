#include "Game-Play-Logic/HistoryState.hpp"

HistoryState::HistoryState() {}

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
}