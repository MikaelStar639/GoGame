#include <Game.hpp>
#include <Window-State/Homescreen.hpp>
#include <Window-State/PlayOptions.hpp>
#include <Window-State/GameScreen.hpp>

#include "UI/Game-Elements/Board.hpp"
#include "UI/Game-Elements/Stone.hpp"

#include <iostream>

Game::Game() : window(sf::VideoMode({1200, 900}), "GoGame"), 
               font("assets/fonts/Monocraft.ttc"){

    windowStateStack.push({windowState::Exit});
    windowStateStack.push({windowState::Homescreen});

    
}

void Game::run(){
    
    sf::Texture backgroundTexture("assets/images/Background.png");
    sf::Texture blackStoneTexture("assets/images/BlackStone.png");
    sf::Texture whiteStoneTexture("assets/images/WhiteStone.png");

    Homescreen homeScreen(font, window, backgroundTexture);
    PlayOptions playOptions(font, window, backgroundTexture);
    GameScreen gameScreen(font, window, blackStoneTexture, whiteStoneTexture, backgroundTexture);

    while (window.isOpen()){
        handleEvent(window);

        window.clear();

        assert(!windowStateStack.empty());
        windowState state = windowStateStack.top();

        if (state == windowState::Exit){
            window.close();
            break;
        }

        if (state == windowState::Homescreen){
            homeScreen.nextState = windowState::Homescreen;
            homeScreen.run();
            state = homeScreen.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::PlayOptions){
            playOptions.nextState = windowState::PlayOptions;
            playOptions.run();
            state = playOptions.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::GameScreen){
            gameScreen.nextState = windowState::GameScreen;
            gameScreen.run();
            state = gameScreen.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::Settings){
            //TODO: Settings
            continue;
        }
    }
}