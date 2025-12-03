#include "Game-Play-Logic/GameState.hpp"

GameState::GameState(sf::Sound &_stoneCaptureSound, sf::Sound &_stoneSound) : 
    stoneCaptureSound(_stoneCaptureSound), stoneSound(_stoneSound) {
    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            grid[y][x] = Stone::State::empty;
        }
    }
}

//*  Game Management
void GameState::addStone(int y, int x, Turn _turn){
    if (_turn == Turn::black){
        grid[y][x] = Stone::State::black;
    }
    else{
        grid[y][x] = Stone::State::white;
    }
}

void GameState::pass(){
    lastMovePass = true;
    
    if (history.index + 1 == static_cast<int>(history.size()))
    {
        history.data.emplace_back(HistoryState());
    }
    
    ++history.index;
    if (turn == Turn::black)
        history[history.index].turn = HistoryState::Turn::black;
    else
        history[history.index].turn = HistoryState::Turn::white;
    
    history[history.index].isPassed = true;
    history.undoCount = 0;

    swapTurn();
}

void GameState::addStoneMove(int y, int x){
    lastMovePass = false;

    if (x == -1){
        pass();
        return;
    }

    addStone(y, x, turn);
    
    // truncate history if we are not at the end
    if (history.index + 1 == static_cast<int>(history.size()))
    {
        history.data.emplace_back(HistoryState());
    }
    
    // push new info state into history.index + 1
    ++history.index;
    if (turn == Turn::black)
        history[history.index].turn = HistoryState::Turn::black;
    else
        history[history.index].turn = HistoryState::Turn::white;
    
    history[history.index].newStone.y = y;
    history[history.index].newStone.x = x;
    RemoveCapturedStones(history[history.index]);
    history.undoCount = 0;

    swapTurn();
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

bool GameState::canCapture(){
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
    else{
        stoneSound.play();
    }

    for (auto &[y, x] : toDelete) {
        historyState.capturedStones.push_back({y, x});
        grid[y][x] = Stone::State::empty;
    }
}

bool GameState::isIllegal(int y, int x) {

    //KO rule
    if (history.index >= 0 && history[history.index].capturedStones.size() == 1){
        auto currentState = history[history.index];
        auto [_y, _x] = currentState.capturedStones[0];
        if (y == _y && _x == x){
            if (static_cast<int>(turn) != static_cast<int>(currentState.turn)){
                return true;
            }
        }
    }

    // Placeholder for illegal move logic
    addStone(y, x, turn);
    int currentLiberties = LibertiesCount(y, x);
    if (currentLiberties > 0)
    {
        deleteStone(y, x); // revert the move
        return false;
    }
    else if (canCapture())
    {
        deleteStone(y, x); // revert the move
        return false;
    }
    deleteStone(y, x); // revert the move
    return true; 
}

void GameState::swapTurn(){
    if (turn == Turn::black){
        turn = Turn::white;
    }
    else{
        turn = Turn::black;
    }
}

//*  end game
void GameState::getScore(){

    blackScore = 0;
    whiteScore = 7; //komi = 7.5

    //* using DFS for easier implementation
    bool visited[19][19] = {false};
    const int dy[4] = {-1, 1, 0, 0};
    const int dx[4] = {0, 0, -1, 1};

    //* lambda
    auto dfs = 
    [&](auto& self, int y, int x, bool &blackAdj, bool &whiteAdj, bool &reachOutside, int &count) -> void {
        visited[y][x] = true;
        ++count;
        for (int t = 0;  t < 4; ++t){
            int nx = x + dx[t], ny = y + dy[t];
            if (ny < 0 || ny >= 19 || nx < 0 || nx >= 19){
                reachOutside = true;
                continue;
            }

            if (grid[ny][nx] == Stone::State::empty){
                if (!visited[ny][nx]){
                    self(self, ny, nx, blackAdj, whiteAdj, reachOutside, count);
                }
            }
            else{
                if (grid[ny][nx] == Stone::State::black){
                    blackAdj = true;
                }
                else{
                    whiteAdj = true;
                }
            }
        }
    };

    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            if (grid[y][x] == Stone::State::black) ++blackScore;
            if (grid[y][x] == Stone::State::white) ++whiteScore;
            if (grid[y][x] == Stone::State::empty){
                if (!visited[y][x]){
                    int count = 0;
                    bool blackAdj = false, whiteAdj = false;
                    bool reachOutside = false;

                    dfs(dfs, y, x, blackAdj, whiteAdj, reachOutside, count);
                    if (reachOutside) continue;
                    if (blackAdj && !whiteAdj){
                        blackScore += count;
                    }
                    if (!blackAdj && whiteAdj){
                        whiteScore += count;
                    }
                }
            }
        }
    }

    // std::cout << "Black: " << blackScore << ", White: " << whiteScore << ".5\n";
}

//* reset
void GameState::reset(){
    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            grid[y][x] = Stone::State::empty;
        }
    }
    lastMovePass = false;
    turn = Turn::black;
    history.reset();
    isEnd = false;
}

//*  undo/redo
void GameState::undo() {
    if (history.index >= 0) {
        HistoryState &state = history[history.index];
        if (!state.isPassed){
            deleteStone(state.newStone.y, state.newStone.x);
        }

        for (auto &[y, x] : state.capturedStones) {
            addStone(y, x, (state.turn == HistoryState::Turn::black) ? Turn::white : Turn::black);
        }

        --history.index;
        history.undoCount++;
        swapTurn();
    }
}

void GameState::redo() {
    if (history.index + 1 < static_cast<int>(history.size()) && history.undoCount > 0) {
        ++history.index;
        HistoryState &state = history[history.index];
        if (!state.isPassed){
            addStone(state.newStone.y, state.newStone.x, 
                      (state.turn == HistoryState::Turn::black) ? Turn::black : Turn::white);
        }
        for (auto &[y, x] : state.capturedStones) {
            deleteStone(y, x);
        }
        history.undoCount--;
        swapTurn();
    }
}

//*  load/save game
void GameState::load(std::string _address){
    std::ifstream fin(_address);

    if (fin.peek() == std::ifstream::traits_type::eof()){
        isFileEmpty = true;
        return;
    }
    else{
        isFileEmpty = false;
        reset();
    }

    //* current state:
    //* turn, lastmovePass, isEnd, grid
    bool _turn;
    fin >> _turn >> lastMovePass >> isEnd;
    turn = static_cast<Turn>(_turn);
    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            int tmp; fin >> tmp;
            grid[y][x] = static_cast<Stone::State>(tmp);
        }
    }
    //* History:
    //* index, undoCount, data
    int sz;
    fin >> history.index >> history.undoCount >> sz;
    for (int i = 0; i < sz; ++i){
        HistoryState state;
        int _turn, _size;
        fin >> _turn >> state.isPassed 
            >> state.newStone.y >> state.newStone.x >> _size; 
        
        state.turn = static_cast<HistoryState::Turn>(_turn);
        for (int i = 0; i < _size; ++i){
            int y, x; fin >> y >> x;
            state.capturedStones.push_back({y, x});
        }

        history.data.push_back(state);
    } 

    fin.close();
}

void GameState::save(std::string _address){
    std::ofstream fout(_address);

    //* current state:
    //* turn, lastmovePass, isEnd, grid
    fout << static_cast<int>(turn) << ' ' << lastMovePass << ' ' << isEnd << '\n';
    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            fout << static_cast<int>(grid[y][x]) << ' ';
        }
        fout << '\n';
    }

    //* History:
    //* index, undoCount, data
    fout << history.index << ' ' << history.undoCount 
         << ' ' << history.data.size() << '\n';

    for (int i = 0; i < history.size(); ++i){
        auto state = history[i];
        fout << static_cast<int>(state.turn) << ' ' 
             << state.isPassed << ' '
             << state.newStone.y << ' ' << state.newStone.x << ' '
             << state.capturedStones.size() << '\n';
        
        for (auto [y, x]: state.capturedStones){
            fout << y << ' ' << x << ' ';
        }
        fout << '\n';
    }

    fout.close();
}

std::vector<Position> GameState::getPossibleMove(){
    std::vector<Position> goodPosition;
    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            if (grid[y][x] == Stone::State::empty && !isIllegal(y, x)){
                goodPosition.push_back({y, x});
            }
        }
    }
    goodPosition.push_back({-1, -1});
    return goodPosition;
}

void GameState::addVirtualMove(int y, int x){

    if (x != -1) addStone(y, x, turn);
    
    if (virtualHistory.index + 1 >= static_cast<int>(virtualHistory.data.size()))
    {
        virtualHistory.data.emplace_back(HistoryState());
    }
    
    ++virtualHistory.index;
    
    HistoryState &currentState = virtualHistory[virtualHistory.index];

    currentState.capturedStones.clear(); 
    currentState.isPassed = false;       
    
    if (turn == Turn::black)
        currentState.turn = HistoryState::Turn::black;
    else
        currentState.turn = HistoryState::Turn::white;
    
    if (x != -1){
        currentState.newStone.y = y;
        currentState.newStone.x = x;
        currentState.isPassed = false; // Đảm bảo chắc chắn
        
        RemoveCapturedStones(currentState); 
    }
    else{
        currentState.isPassed = true;
    }

    virtualHistory.undoCount = 0;

    swapTurn();
}

void GameState::virtualUndo(){
    if (virtualHistory.index >= 0) {
        HistoryState &state = virtualHistory[virtualHistory.index];
        
        if (!state.isPassed){
            deleteStone(state.newStone.y, state.newStone.x);
        }

        Turn capturedTurn = (state.turn == HistoryState::Turn::black) ? Turn::white : Turn::black;
        for (auto &[y, x] : state.capturedStones) {
            addStone(y, x, capturedTurn);
        }

        --virtualHistory.index;
        virtualHistory.undoCount++;
        
        swapTurn();
    }
}

int GameState::minimaxScore(){
    getScore();
    return blackScore - whiteScore;
}