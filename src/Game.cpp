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

Game::Game() : window(sf::VideoMode({1600, 900}), "GoGame", sf::Style::Default ^ sf::Style::Resize), 
               font("assets/fonts/Monocraft.ttc"),
               icon("assets/images/PixelatedBlackStone.png"),
               board      (font, gameTexture),
               homeScreen (font, window, gameTexture),
               gameMenu   (font, window, gameTexture, gameScreen),
               playOptions(font, window, gameTexture, gameScreen),
               settings   (font, window, gameTexture, gameSound),
               gameScreen (font, window, gameTexture, gameSound, board),
               selectBoard(font, window, gameTexture, board),
               selectStone(font, window, gameScreen, gameTexture){

    window.setIcon(icon);
    screenStateStack.push({screenState::Exit});
    screenStateStack.push({screenState::Homescreen});

    screens[screenState::Homescreen]  = &homeScreen;
    screens[screenState::GameMenu]    = &gameMenu;
    screens[screenState::PlayOptions] = &playOptions;
    screens[screenState::Settings]    = &settings;
    screens[screenState::GameScreen]  = &gameScreen;
    screens[screenState::SelectBoard] = &selectBoard;
    screens[screenState::SelectStone] = &selectStone;
}

void Game::addState(screenState state){
    if (state != screenState::Exit)
        screenStateStack.push(state);
    else
        screenStateStack.pop();
}

void Game::handleScreen(){
    screenState state = screenStateStack.top();
    if (state == screenState::Exit){
        window.close();
        return;
    }

    Screen* screen = screens[state];
    screen->run();
    if (state == screenState::PlayOptions){
        if (screen->nextState == screenState::GameScreen){
            addState(screenState::Exit);
        }
    }
    addState(screen->nextState);
}