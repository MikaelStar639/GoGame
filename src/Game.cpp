#include <Game.hpp>
#include <Game-State/Homescreen.hpp>
#include <Game-State/PlayOptions.hpp>

#include <iostream>

Game::Game() : window(sf::VideoMode({1200, 900}), "GoGame"), 
               font("assets/fonts/Monocraft.ttc")
               {
                    gameStateStack.push({gameState::Exit});
                    gameStateStack.push({gameState::Homescreen});
               }

void Game::run(){
    
    while (window.isOpen()){
        handleEvent(window);

        assert(!gameStateStack.empty());
        gameState state = gameStateStack.top();

        if (state == gameState::Exit){
            window.close();
            break;
        }

        if (state == gameState::Homescreen){
            Homescreen homeScreen(font, window);
            homeScreen.run();
            state = homeScreen.nextState;

            if (state != gameState::Exit)
                gameStateStack.push(state);
            else
                gameStateStack.pop();

            continue;
        }

        if (state == gameState::PlayOptions){
            PlayOptions playOptions(font, window);
            playOptions.run();
            state = playOptions.nextState;

            if (state != gameState::Exit)
                gameStateStack.push(state);
            else
                gameStateStack.pop();

            continue;
        }

        if (state == gameState::Settings){
            //TODO: Settings
            continue;
        }
    }
}