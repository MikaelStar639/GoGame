#include "Game-Play-Logic/HistoryState.hpp"
#include <iostream>

HistoryState& History::operator[](int id) {
    return data[id];
}

int History::size(){
    return data.size();
}

void History::reset(){
    index = -1;
    undoCount = 0;
}