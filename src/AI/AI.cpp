#include <AI/AI.hpp>
#include <iostream>

AI::AI(GameState &_gameState) : gameState(_gameState) {}

bool AI::isThinking(){
    return thinking;
}

void AI::stopThinking(){
    std::cout << "Bot stopped thinking\n";
    thinking = false;
}

void AI::think(){

    std::cout << "Bot started thinking\n";

    thinking = true;
    startTime = std::chrono::steady_clock::now();
    GameState gameStateCopy = gameState;
    if (difficulty == 0){
        botFuture = std::async(std::launch::async, [this, gameStateCopy]() mutable {
            return this->getRandomMove(gameStateCopy);
        });
    }
    else{
        botFuture = std::async(std::launch::async, [this, gameStateCopy]() mutable {
            moveScore result = this->minimax(gameStateCopy, -1000000000, 1000000000, true, 0);
            return result.position;
        });
    }
}

bool AI::isReady(){
    if (botFuture.wait_for(std::chrono::seconds(0)) != std::future_status::ready){
        std::cout << "Bot is thinking...\n";
    }
    return botFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

Position AI::getMove(){
    thinking = false;
    std::cout << "Bot played a move after " << getThinkingTime() << "ms\n";
    return botFuture.get();
}

long long AI::getThinkingTime() {
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
}

Position AI::getRandomMove(GameState &gameState){
    auto possibleMove = gameState.getPossibleMove();
    static std::mt19937 rng(time(0)); 

    int idx = rng() % possibleMove.size();
    return possibleMove[idx];
}

int AI::getEvalScore(GameState &gameState){
    int score = gameState.minimaxScore();
    if (!isBlack) score = -score;
    return score;
}

AI::moveScore AI::minimax(GameState &gameState, int alpha, int beta, bool isMax, int depth){

    if (depth == max_depth || getThinkingTime() > 4000){
        return {getEvalScore(gameState), {-1, -1}};
    }

    auto possibleMove = gameState.getPossibleMove();

    Position bestMove = {-1, -1};
    int bestScore;
    if (isMax){
        bestScore = -1000000000;
        for (auto [x, y]: possibleMove){
            if (x == -1 && gameState.lastMovePass){
                int finalScore = getEvalScore(gameState);
                if (finalScore > bestScore){
                    bestScore = finalScore; 
                    bestMove = {-1, -1};
                }
            }
            else{
                gameState.addVirtualMove(x, y);
                int curScore = minimax(gameState, alpha, beta, false, depth + 1).score;
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
                int finalScore = getEvalScore(gameState); 
                if (finalScore < bestScore){
                    bestScore = finalScore; 
                    bestMove = {-1, -1};
                }
            }
            else{
                gameState.addVirtualMove(x, y);
                int curScore = minimax(gameState, alpha, beta, true, depth + 1).score;
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
void AI::setDifficulty(int _difficulty){
    difficulty = _difficulty;
    if (difficulty == 1) max_depth = 2;
    if (difficulty == 2) max_depth = 3;
}