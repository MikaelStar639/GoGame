#include <AI/AI.hpp>

AI::AI(GameState &_gameState) : gameState(_gameState) {}

Position AI::getMove(){
    if (difficulty == 0) return getRandomMove();
    return minimax(-1000000000, 1000000000, true, 0).position;
}

Position AI::getRandomMove(){
    auto possibleMove = gameState.getPossibleMove();
    static std::mt19937 rng(time(0)); 

    int idx = rng() % possibleMove.size();
    return possibleMove[idx];
}

int AI::getEvalScore(){
    int score = gameState.minimaxScore();
    if (!isBlack) score = -score;
    return score;
}

AI::moveScore AI::minimax(int alpha, int beta, bool isMax, int depth){

    static std::mt19937 rng(time(0)); 
    auto possibleMove = gameState.getPossibleMove();
    std::shuffle(possibleMove.begin(), possibleMove.end(), rng);

    if (depth == max_depth){
        return {getEvalScore(), {-1, -1}};
    }

    Position bestMove = {-1, -1};
    int bestScore;
    if (isMax){
        bestScore = -1000000000;
        for (auto [x, y]: possibleMove){
            if (x == -1 && gameState.lastMovePass){
                int finalScore = getEvalScore();
                if (finalScore > bestScore){
                    bestScore = finalScore; 
                    bestMove = {-1, -1};
                }
            }
            else{
                gameState.addVirtualMove(x, y);
                int curScore = minimax(alpha, beta, false, depth + 1).score;
                gameState.virtualUndo();
                if (curScore > bestScore){
                    bestScore = curScore;
                    bestMove = {x, y};
                }
            }

            alpha = std::max(alpha, bestScore);
            if (alpha >= beta){
                return {bestScore, bestMove};
            }
        }
    }
    else{
        bestScore = +1000000000;
        for (auto [x, y]: possibleMove){
            if (x == -1 && gameState.lastMovePass){
                int finalScore = getEvalScore(); 
                if (finalScore < bestScore){
                    bestScore = finalScore; 
                    bestMove = {-1, -1};
                }
            }
            else{
                gameState.addVirtualMove(x, y);
                int curScore = minimax(alpha, beta, true, depth + 1).score;
                gameState.virtualUndo();
                if (curScore < bestScore){
                    bestScore = curScore;
                    bestMove = {x, y};
                }
            }

            beta = std::min(beta, bestScore);
            if (alpha >= beta){
                return {bestScore, bestMove};
            }
        } 
    }

    return {bestScore, bestMove};
}

//0: easy, 1: medium, 2: hard
void AI::changeDifficulty(int _difficulty){
    difficulty = _difficulty;
    if (difficulty == 2) max_depth = 2;
    if (difficulty == 3) max_depth = 4;
}