#include <Game.hpp>

void Game::run(){
    while (window.isOpen()){
        handleEvent(window);
        handleScreen();

        if (screenStateStack.top() == screenState::Exit){
            break;
        }
    }
}

Game::Game() : window(sf::VideoMode({1200, 900}), "GoGame", sf::Style::Default ^ sf::Style::Resize), 
               font("assets/fonts/Monocraft.ttc"),
               icon("assets/images/PixelatedBlackStone.png"),
               board(font),
               homeScreen (font, window, gameTexture),
               gameMenu   (font, window, gameTexture),
               settings   (font, window, gameTexture, gameSound),
               gameScreen (font, window, gameTexture, gameSound, board),
               selectBoard(font, window, gameTexture, board),
               selectStone(font, window, gameScreen, gameTexture){

    window.setIcon(icon);
    screenStateStack.push({screenState::Exit});
    screenStateStack.push({screenState::Homescreen});
}

void Game::handleScreen(){
    screenState state = screenStateStack.top();

    if (state == screenState::Exit){
        window.close();
        return;
    }

    if (state == screenState::Homescreen){
        homeScreen.nextState = screenState::Homescreen;
        homeScreen.run();
        state = homeScreen.nextState;

        if (state != screenState::Exit)
            screenStateStack.push(state);
        else
            screenStateStack.pop();

        return;
    }

    if (state == screenState::GameMenu){
        gameMenu.nextState = screenState::GameMenu;
        gameMenu.run();

        if (gameMenu.loadGame == true){
            gameMenu.loadGame = false;
            gameScreen.loadGame("game.saves");
        }
        if (gameMenu.saveGame == true){
            gameScreen.saveGame("game.saves");
            gameMenu.saveGame = false;
            gameMenu.nextState = screenState::GameMenu;
        }

        state = gameMenu.nextState;

        if (state != screenState::Exit)
            screenStateStack.push(state);
        else
            screenStateStack.pop();

        return;
    }

    if (state == screenState::NewGame){
        gameScreen.reset();
        gameScreen.canNotLoad = false;
        gameScreen.nextState = screenState::GameScreen;
        gameScreen.run();
        
        state = gameScreen.nextState;
        if (state != screenState::Exit)
            screenStateStack.push(state);
        else
            screenStateStack.pop();

        return;
    }

    if (state == screenState::Resume){
        if (gameScreen.canNotLoad){
            screenStateStack.pop();
            state = screenStateStack.top();
            return;
        }
        
        gameScreen.nextState = screenState::GameScreen;
        gameScreen.run();
        
        state = gameScreen.nextState;
        if (state != screenState::Exit)
            screenStateStack.push(state);
        else
            screenStateStack.pop();

        return;
    }

    if (state == screenState::Settings){
        settings.nextState = screenState::Settings;
        settings.run();
        state = settings.nextState;

        if (state != screenState::Exit)
            screenStateStack.push(state);
        else
            screenStateStack.pop();

        return;
    }

    if (state == screenState::SelectBoard){
        selectBoard.nextState = screenState::SelectBoard;
        selectBoard.run();
        state = selectBoard.nextState;

        if (state != screenState::Exit)
            screenStateStack.push(state);
        else
            screenStateStack.pop();

        return;
    }

    if (state == screenState::SelectStone){
        selectStone.nextState = screenState::SelectStone;
        selectStone.run();
        state = selectStone.nextState;

        if (state != screenState::Exit)
            screenStateStack.push(state);
        else
            screenStateStack.pop();

        return;
    }
}