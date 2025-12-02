#include "Game-Play-Logic/GameState.hpp"
#include "random"


class AI{
private:
    int difficulty = 1;
    int max_depth = 2;
    bool isBlack = false;
    GameState &gameState;

    Position getRandomMove();

    struct moveScore{
        int score;
        Position position;
    };

    int getEvalScore();
    moveScore minimax(int alpha, int beta, bool isMax, int depth);

public:
    AI(GameState &gameState);
    Position getMove();
    void changeDifficulty(int difficulty);
};