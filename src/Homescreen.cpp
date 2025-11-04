#include "Game-State/Homescreen.hpp"

Homescreen::Homescreen(sf::Font &font, sf::RenderWindow &_window) : 
    playButton(font),
    resumeButton(font),
    settingButton(font),
    exitButton(font),
    window(_window){
        playButton.   setString("Play");
        resumeButton. setString("Resume");
        settingButton.setString("Setting");
        exitButton.   setString("Exit");
    }

void Homescreen::updateButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    playButton.   setPosition({window_w/2, window_h * 1/5});
    resumeButton. setPosition({window_w/2, window_h * 2/5});
    settingButton.setPosition({window_w/2, window_h * 3/5});
    exitButton.   setPosition({window_w/2, window_h * 4/5});

    //Buttons setSize
    playButton.   setSize({500.f, 100.f});
    resumeButton. setSize({500.f, 100.f});
    settingButton.setSize({500.f, 100.f});
    exitButton.   setSize({500.f, 100.f});

    //buttons update
    playButton.   update(mouse);
    resumeButton. update(mouse);
    settingButton.update(mouse);
    exitButton.   update(mouse);

    //check if any button is clicked
    if (playButton.onRelease)    nextState = Game::gameState::PlayOptions;
    if (resumeButton.onRelease)  nextState = Game::gameState::Resume;
    if (settingButton.onRelease) nextState = Game::gameState::Settings;
    if (exitButton.onRelease)    nextState = Game::gameState::Exit;
}

void Homescreen::drawButton(){
    playButton.   draw(window);
    resumeButton. draw(window);
    settingButton.draw(window);
    exitButton.   draw(window);
}

void Homescreen::setBackground(sf::Sprite &backgroundSprite){

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

void Homescreen::run(){

    //mouse
    Mouse mouse;

    //background
    sf::Texture backgroundTexture("assets/images/homescreenBackground.png");
    sf::Sprite backgroundSprite(backgroundTexture);

    while (window.isOpen()){
        handleEvent(window);

        //Background
        window.clear();
        setBackground(backgroundSprite);

        //mouse update
        mouse.update(window);
        updateButton(mouse);

        //just draw :v
        drawButton();
        window.display();
        
        //if the state is not homescreen (some button was clicked)
        if (nextState != Game::gameState::Homescreen){
            break;
        }
    }
}