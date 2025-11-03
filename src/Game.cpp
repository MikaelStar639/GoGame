#include <Game.hpp>
#include "Input/Mouse.hpp"

Game::Game() : window(sf::VideoMode({1200, 900}), "GoGame"), 
               font("assets/fonts/Monocraft.ttc"),
               state(gameState::Homescreen) 
               {}

void Game::run(){
    
    while (window.isOpen()){
        handleEvent(window);
        if (state == gameState::Homescreen){
            //TODO: Homescreen
            window.display();
            continue;
        }
        if (state == gameState::PlayOptions){
            //TODO: Play Options

            window.display();
            continue;
        }
        if (state == gameState::Settings){
            //TODO: Settings

            window.display();
            continue;
        }
    }
}