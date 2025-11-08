#include "Game-Play-Logic/GameState.hpp"

GameState::GameState() {
    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            grid[y][x] = Stone::State::empty;
        }
    }
}

void GameState::addStone(int y, int x){
    if (turn == Turn::black){
        grid[y][x] = Stone::State::black;
    }
    else{
        grid[y][x] = Stone::State::white;
    }
}

void GameState::deleteStone(int y, int x){
    grid[y][x] = Stone::State::empty;
}