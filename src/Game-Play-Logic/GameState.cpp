#include "Game-Play-Logic/GameState.hpp"
#include <iostream>

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
    if (history.index + 1 == static_cast<int>(history.size()))
    {
        std::vector<std::pair<int, int>> emptyCaptured;
        emptyCaptured.resize(0);
        HistoryState emptyState(HistoryState::Turn::black, 0, 0, emptyCaptured);
        history.data.emplace_back(emptyState);
    }
    
    // push new info state into history.index + 1
    ++history.index;
    if (turn == Turn::black)
        history[history.index].turn = HistoryState::Turn::black;
    else
        history[history.index].turn = HistoryState::Turn::white;
    
    history[history.index].y_newStone = y;
    history[history.index].x_newStone = x;
    RemoveCapturedStones(history[history.index]);
    history.undoCount = 0;

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
    }

    for (auto &[y, x] : toDelete) {
        historyState.capturedStones.push_back({y, x});
        grid[y][x] = Stone::State::empty;
    }
}

bool GameState::isIllegal(int y, int x, GameState::Turn _turn) {

    //KO rule
    if (history.index >= 0 && history[history.index].capturedStones.size() == 1){
        auto currentState = history[history.index];
        auto [_y, _x] = currentState.capturedStones[0];
        if (y == _y && _x == x){
            if (static_cast<int>(_turn) != static_cast<int>(currentState.turn)){
                return true;
            }
        }
    }

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

void GameState::undo() {
    if (history.index >= 0) {
        HistoryState &state = history[history.index];
        deleteStone(state.y_newStone, state.x_newStone);
        for (auto &[y, x] : state.capturedStones) {
            addStone(y, x, (state.turn == HistoryState::Turn::black) ? Turn::white : Turn::black);
        }
        turn = (state.turn == HistoryState::Turn::black) ? Turn::white : Turn::black;
        --history.index;
        history.undoCount++;
    }
}

void GameState::redo() {

    if (history.index + 1 < static_cast<int>(history.size()) && history.undoCount > 0) {
        ++history.index;
        HistoryState &state = history[history.index];
        addStone(state.y_newStone, state.x_newStone, 
                  (state.turn == HistoryState::Turn::black) ? Turn::black : Turn::white);
        for (auto &[y, x] : state.capturedStones) {
            deleteStone(y, x);
        }
        turn = (state.turn == HistoryState::Turn::black) ? Turn::white : Turn::black;
        history.undoCount--;
    }
}

void GameState::load(std::string _address){
    std::ifstream fin;
    fin.open(_address);

    if (fin.peek() == std::ifstream::traits_type::eof()){
        isFileEmpty = true;
        return;
    }
    isFileEmpty = false;

    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            grid[y][x] = Stone::State::empty;
        }
    }

    int black_num, white_num;
    fin >> black_num;
    for (int i = 0; i < black_num; ++i){
        int y, x; fin >> y >> x;
        grid[y][x] = Stone::State::black; 
    }

    fin >> white_num;
    for (int i = 0; i < black_num; ++i){
        int y, x; fin >> y >> x;
        grid[y][x] = Stone::State::white; 
    }

    if (black_num == 0 && white_num == 0) isFileEmpty = true;
    fin.close();
}

void GameState::save(std::string _address){
    std::ofstream fout(_address);

    int black_num, white_num;
    std::vector<std::pair<int, int>> temp;
    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            if (grid[y][x] == Stone::State::black){
                temp.push_back({y, x});
            }
        }
    }

    fout << temp.size() << ' ';
    for (auto [y, x]: temp) fout << y << ' ' << x << ' ';
    fout << '\n';
    temp.clear();

    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            if (grid[y][x] == Stone::State::white){
                temp.push_back({y, x});
            }
        }
    }

    fout << temp.size() << ' ';
    for (auto [y, x]: temp) fout << y << ' ' << x << ' ';
    fout << '\n';
    temp.clear();

    fout.close();
}