#include "Game-State/PlayOptions.hpp"


PlayOptions::PlayOptions(sf::Font &font, sf::RenderWindow &_window) : 
    pvbButton (font),
    pvpButton (font),
    backButton(font),
    window(_window){
        pvbButton. setString("Two Player - One Device Mode");
        pvpButton. setString("Player vs AI");
        backButton.setString("Back");
    }

void PlayOptions::updateButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;
    


    //Buttons setPosition
    float space = 125.f;
    
    pvbButton. setPosition({window_w/2, window_h/2 - space});
    pvpButton. setPosition({window_w/2, window_h/2});
    backButton.setPosition({window_w/2, window_h/2 + space});

    //Buttons setSize
    pvbButton. setSize({725.f, 75.f});
    pvpButton. setSize({725.f, 75.f});
    backButton.setSize({725.f, 75.f});

    //buttons update
    pvbButton. update(mouse);
    pvpButton. update(mouse);
    backButton.update(mouse);

    //check if any button is clicked
    if (pvbButton.onRelease)  nextState = Game::gameState::GamePlay;
    if (pvpButton.onRelease)  nextState = Game::gameState::GamePlay;
    if (backButton.onRelease) nextState = Game::gameState::Exit;
}

void PlayOptions::drawButton(){
    pvbButton. draw(window);
    pvpButton. draw(window);
    backButton.draw(window);
}

void PlayOptions::setBackground(sf::Sprite &backgroundSprite){

    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    float scale = window_h/backgroundSprite.getTexture().getSize().y;
    backgroundSprite.setScale({scale, scale});

    float size_x = backgroundSprite.getTexture().getSize().x;
    float size_y = backgroundSprite.getTexture().getSize().y;
    
    backgroundSprite.setOrigin({size_x/2, size_y/2});
    backgroundSprite.setPosition({window_w/2, window_h/2});

    
    window.draw(backgroundSprite);
}

void PlayOptions::run(){

    //mouse
    Mouse mouse;

    //background
    sf::Texture backgroundTexture("assets/images/homescreenBackground.png");
    sf::Sprite backgroundSprite(backgroundTexture);

    while (window.isOpen()){
        handleEvent(window);

        //window sizes
        float window_w = window.getSize().x;
        float window_h = window.getSize().y;

        //Background
        window.clear();
        setBackground(backgroundSprite);

        //mouse update
        mouse.update(window);

        //update position and size
        updateButton(mouse);

        //just draw :v
        drawButton();
        
        window.display();
        
        //if the state is not PlayOptions (some button was clicked)
        if (nextState != Game::gameState::PlayOptions){
            break;
        }
    }
}