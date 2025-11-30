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
               board      (font, gameTexture),
               homeScreen (font, window, gameTexture),
               gameMenu   (font, window, gameTexture, gameScreen),
               settings   (font, window, gameTexture, gameSound),
               gameScreen (font, window, gameTexture, gameSound, board),
               selectBoard(font, window, gameTexture, board),
               selectStone(font, window, gameScreen, gameTexture){

    window.setIcon(icon);
    screenStateStack.push({screenState::Exit});
    screenStateStack.push({screenState::Homescreen});
}

void Game::addState(screenState state){
    if (state != screenState::Exit)
        screenStateStack.push(state);
    else
        screenStateStack.pop();
}

template<class currentScreen>
void Game::updateScreen(currentScreen& screen){
    screen.run();
    screenState state = screen.nextState;
    addState(state);
}

void Game::handleScreen(){
    screenState state = screenStateStack.top();

    switch (state){
        case screenState::Exit:
            window.close();
            break;
        
        case screenState::Homescreen:
            homeScreen.nextState = screenState::Homescreen;
            updateScreen(homeScreen);
            break;

        case screenState::GameMenu:
            gameMenu.nextState = screenState::GameMenu;
            updateScreen(gameMenu);
            break;

        case screenState::GameScreen:
            gameScreen.nextState = screenState::GameScreen;
            updateScreen(gameScreen);
            break;

        case screenState::Settings:
            settings.nextState = screenState::Settings;
            updateScreen(settings);
            break;

        case screenState::SelectBoard:
            selectBoard.nextState = screenState::SelectBoard;
            updateScreen(selectBoard);
            break;

        case screenState::SelectStone:
            selectStone.nextState = screenState::SelectStone;
            updateScreen(selectStone);
            break; 
        }
    
}