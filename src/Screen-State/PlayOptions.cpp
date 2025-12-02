#include "Screen-State/PlayOptions.hpp"


PlayOptions::PlayOptions(sf::Font &font, sf::RenderWindow &_window, TextureManager &textures, GameScreen &_gameScreen) : 
    pvpButton (font),
    pvbButton (font),
    backButton(font),
    backgroundSprite(textures["Background"]),
    window(_window), 
    gameScreen(_gameScreen){
        pvpButton. setString("Two Player - One Device");
        pvbButton. setString("Player vs Bot  ");
        backButton.setString("Back");
    }

void PlayOptions::updateButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    float space = 75.f;
    
    pvpButton. setPosition({window_w/2, window_h/2 - space});
    pvbButton. setPosition({window_w/2, window_h/2 + space/2});
    backButton.setPosition({105.f, 50.f});

    //Buttons setSize
    pvpButton. setSize({650.f, 75.f});
    pvbButton. setSize({650.f, 75.f});
    backButton.setSize({200.f, 60.f});

    //buttons update
    pvpButton. update(mouse);
    pvbButton. update(mouse);
    backButton.update(mouse);
}

void PlayOptions::updateScreenState(){
    if (pvpButton .onRelease) nextState = screenState::GameScreen, gameScreen.isAIMode = false;
    if (pvbButton .onRelease) nextState = screenState::GameScreen, gameScreen.isAIMode = true;
    if (backButton.onRelease) nextState = screenState::Exit;
}

void PlayOptions::drawButton(){
    pvpButton. draw(window);
    pvbButton. draw(window);
    backButton.draw(window);
}

void PlayOptions::setBackground(){

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

    nextState = screenState::PlayOptions;

    //mouse
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        //Background
        window.clear();
        setBackground();

        //update
        mouse.update(window);
        updateButton(mouse);
        updateScreenState();

        //just draw :v
        drawButton();
        window.display();
        
        //if the state is not PlayOptions (some button was clicked)
        if (nextState != screenState::PlayOptions){
            break;
        }
    }
}