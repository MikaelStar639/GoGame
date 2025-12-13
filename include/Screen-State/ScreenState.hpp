#pragma once

enum class screenState{
    Homescreen,
    GameMenu,
    PlayOptions,
    Settings,
    SelectBoard,
    SelectStone,
    GameScreen,
    Exit
};

class Screen{
public: 
    screenState nextState;
    virtual ~Screen() = default;
    virtual void run() = 0;
};