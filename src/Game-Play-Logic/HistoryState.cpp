#include "Game-Play-Logic/HistoryState.hpp"

HistoryState& History::operator[](int id) {
    return data[id];
}

int History::size(){
    return data.size();
}

void History::load(std::string _address){
    std::ifstream fin;
    fin.open(_address);

    
}

