#pragma once

#include <SFML/Audio.hpp>
#include <UI/Game-Elements/Stone.hpp>
#include <Game-Play-Logic/HistoryState.hpp>
#include <algorithm>
#include <vector>
#include <queue>

class GameState{
private:
    sf::Sound &stoneCaptureSound;
    sf::Sound &stoneSound;

public:
    enum class Turn{
        black,
        white
    };

    GameState(sf::Sound &stoneCaptureSound, sf::Sound &stoneSound);

    //* Game Elements
    Turn turn = Turn::black;
    bool lastMovePass = false;
    Stone::State grid[19][19];
    History history;

    //* Game Management
    void addStone(int y, int x, Turn _turn);
    void deleteStone(int y, int x);
    bool isIllegal(int y, int x, GameState::Turn turn);
    bool canCapture(GameState::Turn turn);
    int  LibertiesCount(int y, int x);
    void addStoneMove(int y, int x);
    void pass();
    void RemoveCapturedStones(HistoryState &historyState);


    //* End Game State
    bool isEnd = false;
    int blackScore = 0;
    int whiteScore = 0;
    void getScore();
    void reset();

    //*  redo and undo
    void redo();
    bool undo();

    //* load/save game
    bool isFileEmpty = true;
    void load(std::string _address);
    void save(std::string _address);

    //* copy to the other GameState
    void copyTo(GameState &_gameState);
}; 

