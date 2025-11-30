#include "Screen-State/Homescreen.hpp"

Homescreen::Homescreen(sf::Font &font, sf::RenderWindow &_window, TextureManager& _gameTexture) : 
    playButton(font),
    settingButton(font),
    exitButton(font),
    Gamename(font),
    backgroundSprite(_gameTexture["Background"]),
    window(_window){
        playButton.   setString("Play");
        settingButton.setString("Setting");
        exitButton.   setString("Exit");
        Gamename.     setString("Go Game");
    }

void Homescreen::updateButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    playButton.   setPosition({window_w/2, window_h * 13/30});
    settingButton.setPosition({window_w/2, window_h * 18/30});
    exitButton.   setPosition({window_w/2, window_h * 23/30});

    //Buttons setSize
    playButton.   setSize({500.f, 100.f});
    settingButton.setSize({500.f, 100.f});
    exitButton.   setSize({500.f, 100.f});

    //buttons update
    playButton.   update(mouse);
    settingButton.update(mouse);
    exitButton.   update(mouse);
}

void Homescreen::updateScreenState(){
    if (playButton.onRelease)    nextState = screenState::GameMenu;
    if (settingButton.onRelease) nextState = screenState::Settings;
    if (exitButton.onRelease)    nextState = screenState::Exit;
}

void Homescreen::drawButton(){
    playButton.   draw(window);
    settingButton.draw(window);
    exitButton.   draw(window);
}

void Homescreen::setBackground(){

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

    Gamename.setPosition({window_w/2, window_h * 2/10});
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

    nextState = screenState::Homescreen;

    //mouse
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        //Background
        window.clear();
        setBackground();
        UpdateGamenamePosition();

        //mouse update
        mouse.update(window);
        updateButton(mouse);

        //screen update
        updateScreenState();

        //display
        drawButton();
        drawGamename();
        window.display();
        
        if (nextState != screenState::Homescreen){
            break;
        }
    }
}