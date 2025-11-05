#include <Game.hpp>
#include <Window-State/Homescreen.hpp>
#include <Window-State/PlayOptions.hpp>
#include <Window-State/Gameplay.hpp>

#include <iostream>

Game::Game() : window(sf::VideoMode({1200, 900}), "GoGame"), 
               font("assets/fonts/Monocraft.ttc")
               {
                    windowStateStack.push({windowState::Exit});
                    windowStateStack.push({windowState::Homescreen});
               }

void Game::run(){
    
    while (window.isOpen()){
        handleEvent(window);

        assert(!windowStateStack.empty());
        windowState state = windowStateStack.top();

        if (state == windowState::Exit){
            window.close();
            break;
        }

        if (state == windowState::Homescreen){
            Homescreen homeScreen(font, window);
            homeScreen.run();
            state = homeScreen.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::PlayOptions){
            PlayOptions playOptions(font, window);
            playOptions.run();
            state = playOptions.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::GamePlay){
            // Gameplay gamePlay(font, window);
            // gamePlay.run();
            // state = gamePlay.nextState;

            // if (state != windowState::Exit)
            //     windowStateStack.push(state);
            // else
            //     windowStateStack.pop();

            continue;
        }

        if (state == windowState::Settings){
            //TODO: Settings
            continue;
        }
    }
}