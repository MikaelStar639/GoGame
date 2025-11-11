#include "Window-State/PlayOptions.hpp"


PlayOptions::PlayOptions(sf::Font &font, sf::RenderWindow &_window, sf::Texture &BackgroundTexture) : 
    pvbButton (font),
    pvpButton (font),
    backButton(font),
    BackgroundSprite(BackgroundTexture),
    window(_window){
        pvbButton. setString("Two Player - One Device");
        pvpButton. setString("Player vs Bot  ");
        backButton.setString("Back");
    }

void PlayOptions::updateButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    float space = 75.f;
    
    pvbButton. setPosition({window_w/2, window_h/2 - space});
    pvpButton. setPosition({window_w/2, window_h/2 + space/2});
    backButton.setPosition({105.f, 50.f});

    //Buttons setSize
    pvbButton. setSize({650.f, 75.f});
    pvpButton. setSize({650.f, 75.f});
    backButton.setSize({200.f, 60.f});

    //buttons update
    pvbButton. update(mouse);
    pvpButton. update(mouse);
    backButton.update(mouse);

    //check if any button is clicked
    if (pvbButton .onRelease) nextState = Game::windowState::GameScreen;
    if (pvpButton .onRelease) nextState = Game::windowState::GameScreen;
    if (backButton.onRelease) nextState = Game::windowState::Exit;
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

    while (window.isOpen()){
        handleEvent(window);

        //Background
        window.clear();
        setBackground(BackgroundSprite);

        //update
        mouse.update(window);
        updateButton(mouse);

        //just draw :v
        drawButton();
        window.display();
        
        //if the state is not PlayOptions (some button was clicked)
        if (nextState != Game::windowState::PlayOptions){
            break;
        }
    }
}