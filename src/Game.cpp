#include <Game.hpp>
#include <iostream>

Game::Game() : window(sf::VideoMode({1200, 900}), "GoGame"), 
               font("assets/fonts/Monocraft.ttc"),
               state(gameState::Homescreen) 
               {}

void Game::run(){
    
    while (window.isOpen()){
        handleEvent(window);
        
        if (state == gameState::Homescreen){
            Homescreen homeScreen(font, window);
            homeScreen.run();
            state = homeScreen.nextState;
            continue;
        }
        if (state == gameState::PlayOptions){
            //TODO: Play Options
            break;
        }
        if (state == gameState::Settings){
            //TODO: Settings
            break;
        }
    }
}