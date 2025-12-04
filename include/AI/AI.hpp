#include "Game-Play-Logic/GameState.hpp"
#include "future"
#include "chrono"
#include "random"


class AI{
private:
    int difficulty = 1;
    int max_depth = 2;
    bool isBlack = false;
    GameState &gameState;
    
    struct moveScore{
        int score;
        Position position;
    };
    
    int getEvalScore(GameState &gameState);
    Position getRandomMove(GameState& _gameState);
    moveScore minimax(GameState& _gameState, int alpha, int beta, bool isMax, int depth);
    std::future<Position> botFuture;

    std::chrono::steady_clock::time_point startTime;
    bool thinking;

public:
    AI(GameState &gameState);
    void setDifficulty(int difficulty);
    
    bool isThinking();
    void stopThinking();
    void think();
    bool isReady();
    Position getMove();
    long long getThinkingTime();
};