#include "Game-Play-Logic/GameState.hpp"
// #include "Game-Play-Logic/HistoryState.hpp"
#include <iostream>
#include <SFML/Audio.hpp>

GameState::GameState(sf::Sound &_stoneCaptureSound) : stoneCaptureSound(_stoneCaptureSound) {
    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            grid[y][x] = Stone::State::empty;
        }
    }
}

void GameState::addStone(int y, int x, Turn _turn){
    if (_turn == Turn::black){
        grid[y][x] = Stone::State::black;
    }
    else{
        grid[y][x] = Stone::State::white;
    }
}

void GameState::addStoneMove(int y, int x){
    addStone(y, x, turn);
    // modify historyState here
    
    // truncate history if we are not at the end
    if (HistoryIndex + 1 == static_cast<int>(history.size()))
    {
        HistoryState emptyState(HistoryState::Turn::black, 0, 0, {});
        history.push_back(emptyState);
    }
    
    
    // push new info state into HistoryIndex + 1
    ++HistoryIndex;
    if (turn == Turn::black)
    history[HistoryIndex].turn = HistoryState::Turn::black;
    else
    history[HistoryIndex].turn = HistoryState::Turn::white;
    
    history[HistoryIndex].y_newStone = y;
    history[HistoryIndex].x_newStone = x;
    RemoveCapturedStones(history[HistoryIndex]);
    if (HistoryIndex - 1 >= 0)
    {
        history[HistoryIndex - 1].canredo = false;
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

bool GameState::isIllegal(int y, int x, GameState::Turn _turn) {
    // Placeholder for illegal move logic
    addStone(y, x, _turn);
    int currentLiberties = LibertiesCount(y, x);
    if (currentLiberties > 0)
    {
        deleteStone(y, x); // revert the move
        return false;
    }
    else if (canCapture(_turn))
    {
        deleteStone(y, x); // revert the move
        return false;
    }
    deleteStone(y, x); // revert the move
    return true; 
}

void GameState::RemoveCapturedStones(HistoryState& historyState) {
    // also construct captured stones list for history state
    Stone::State opponent = (turn == Turn::black) ? Stone::State::white : Stone::State::black;
    std::vector<std::pair<int, int>> toDelete;
    for (int y = 0; y < 19; ++y) {
        for (int x = 0; x < 19; ++x){
            if (grid[y][x] != opponent) continue;
            if (LibertiesCount(y, x) == 0) {
                toDelete.push_back({y, x});
            }
        }
    }

    if (!toDelete.empty()){
        stoneCaptureSound.play();
        std::cout << "boom\n";
    }

    for (auto &[y, x] : toDelete) {
        historyState.capturedStones.push_back({y, x});
        grid[y][x] = Stone::State::empty;
    }
}

void GameState::undo() {
    if (HistoryIndex >= 0) {
        HistoryState &state = history[HistoryIndex];
        deleteStone(state.y_newStone, state.x_newStone);
        for (auto &[y, x] : state.capturedStones) {
            addStone(y, x, (state.turn == HistoryState::Turn::black) ? Turn::white : Turn::black);
        }
        turn = (state.turn == HistoryState::Turn::black) ? Turn::white : Turn::black;
        --HistoryIndex;
        history[HistoryIndex].canredo = true;
    }
}

void GameState::redo() {
    if (HistoryIndex + 1 < static_cast<int>(history.size()) && history[HistoryIndex].canredo) {
        ++HistoryIndex;
        HistoryState &state = history[HistoryIndex];
        addStone(state.y_newStone, state.x_newStone, 
                  (state.turn == HistoryState::Turn::black) ? Turn::black : Turn::white);
        for (auto &[y, x] : state.capturedStones) {
            deleteStone(y, x);
        }
        turn = (state.turn == HistoryState::Turn::black) ? Turn::white : Turn::black;
    }
}