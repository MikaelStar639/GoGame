#include "Game-Play-Logic/GameState.hpp"
#include <iostream>

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

int GameState::LibertiesCount(int y, int x) {
    // using BFS to count liberties
    std::queue<std::pair<int,int>> q;
    bool visited[19][19] = {false};
    Stone::State color = grid[y][x];
    int liberties = 0;
    q.push({y, x});
    visited[y][x] = true;
    const int dy[4] = {-1, 1, 0, 0};
    const int dx[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [cy, cx] = q.front();
        q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if (ny < 0 || ny >= 19 || nx < 0 || nx >= 19) continue;
            if (visited[ny][nx]) continue;
            if (grid[ny][nx] == Stone::State::empty) {
                ++liberties;
            } else if (grid[ny][nx] == color) {
                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }
    }
    return liberties;
}

bool GameState::canCapture(GameState::Turn turn) {
    // Placeholder for capture logic
    Stone::State opponent = (turn == Turn::black) ? Stone::State::white : Stone::State::black;
    for (int y = 0; y < 19; ++y) {
        for (int x = 0; x < 19; ++x){
            if (grid[y][x] != opponent) continue;
            if (LibertiesCount(y, x) == 0) return true;
        }
    }
    return false;
}

bool GameState::isIllegal(int y, int x, GameState::Turn turn) {
    // Placeholder for illegal move logic
    addStone(y, x);
    int currentLiberties = LibertiesCount(y, x);
    if (currentLiberties > 0) return false;
    else if (canCapture(turn)) return false;
    deleteStone(y, x);
    return true; 
}

void GameState::RemoveCapturedStones(std::vector<std::vector<Stone>> &stoneGrid) {
    // Placeholder for removing captured stones
    Stone::State opponent = (turn == Turn::black) ? Stone::State::white : Stone::State::black;
    std::vector<std::pair<int, int>> toDelete;
    // std::cout<<"Y "<<'\n';
    for (int y = 0; y < 19; ++y) {
        for (int x = 0; x < 19; ++x){
            if (grid[y][x] != opponent) continue;
            if (LibertiesCount(y, x) == 0) {
                toDelete.push_back({y, x});
            }
        }
    }
    for (auto &[y, x] : toDelete) {
        stoneGrid[y][x].setState(Stone::State::empty);
        grid[y][x] = Stone::State::empty;
    }
}