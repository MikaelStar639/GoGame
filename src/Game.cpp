#include <Game.hpp>

void Game::handleEvent(){
    while (auto event = window.pollEvent()){
        if (event->is<sf::Event::Closed>()){
            window.close();
            break;
        }
        if (event->is<sf::Event::Resized>()){
            sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
            window.setView(view);
        }
    }
}

Game::Game() : window(sf::VideoMode({1200, 900}), "GoGame"), 
               font("assets/fonts/Monocraft.ttc") 
               {}

void Game::run(){
    while (window.isOpen()){
        handleEvent();
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