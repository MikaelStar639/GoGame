#include "Window-State/Homescreen.hpp"

Homescreen::Homescreen(sf::Font &font, sf::RenderWindow &_window, sf::Texture &BackgroundTexture) : 
    playButton(font),
    resumeButton(font),
    settingButton(font),
    exitButton(font),
    Gamename(font),
    BackgroundSprite(BackgroundTexture),
    window(_window){
        playButton.   setString("Play");
        resumeButton. setString("Resume");
        settingButton.setString("Setting");
        exitButton.   setString("Exit");
        Gamename.     setString("Go Game");
    }

void Homescreen::updateButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    playButton.   setPosition({window_w/2, window_h * 3/10});
    resumeButton. setPosition({window_w/2, window_h * 9/20});
    settingButton.setPosition({window_w/2, window_h * 12/20});
    exitButton.   setPosition({window_w/2, window_h * 15/20});

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
    if (playButton.onRelease)    nextState = Game::windowState::PlayOptions;
    if (resumeButton.onRelease)  nextState = Game::windowState::Resume;
    if (settingButton.onRelease) nextState = Game::windowState::Settings;
    if (exitButton.onRelease)    nextState = Game::windowState::Exit;
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

void Homescreen::UpdateGamenamePosition(){
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    Gamename.setPosition({window_w/2, window_h * 1/10});
}

void Homescreen::drawGamename(){
    Gamename.setCharacterSize(150);
    Gamename.setFillColor(sf::Color(143, 150, 179));
    alignText(Gamename, 0.5f, 0.6f);
    Gamename.setOutlineColor(sf::Color(40,40,40));
    Gamename.setOutlineThickness(5.f);
    window.draw(Gamename);
}

void Homescreen::run(){

    //mouse
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        //Background
        window.clear();
        setBackground(BackgroundSprite);
        UpdateGamenamePosition();

        //mouse update
        mouse.update(window);
        updateButton(mouse);

        //just draw :v
        drawButton();
        drawGamename();
        window.display();
        
        //if the state is not homescreen (some button was clicked)
        if (nextState != Game::windowState::Homescreen){
            break;
        }
    }
}