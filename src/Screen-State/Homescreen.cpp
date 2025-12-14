#include "Screen-State/Homescreen.hpp"

Homescreen::Homescreen(sf::Font &_font, sf::RenderWindow &_window, TextureManager& _gameTexture) : 
    playButton      (_font),
    settingButton   (_font),
    exitButton      (_font),
    Gamename        (_font),
    window          (_window),
    backgroundSprite(_gameTexture["Background"])
{
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    playButton   .setPosition({window_w/2, window_h * 13/30});
    settingButton.setPosition({window_w/2, window_h * 18/30});
    exitButton   .setPosition({window_w/2, window_h * 23/30});
    Gamename     .setPosition({window_w/2, window_h * 2/10});


    //Buttons setSize
    playButton   .setSize({500.f, 100.f});
    settingButton.setSize({500.f, 100.f});
    exitButton   .setSize({500.f, 100.f});
    
    //Buttons setString
    playButton   .setString("Play");
    settingButton.setString("Setting");
    exitButton   .setString("Exit");
    Gamename     .setString("Go Game");

    Gamename.setCharacterSize(150);
    Gamename.setFillColor(sf::Color(250, 250, 250));
    Gamename.setOutlineColor(sf::Color(40, 40, 40));
    Gamename.setOutlineThickness(5.f);
    alignText(Gamename, 0.5f, 0.6f);

    float scale = window_h/backgroundSprite.getTexture().getSize().y;
    backgroundSprite.setScale({scale, scale});

    float size_x = backgroundSprite.getTexture().getSize().x;
    float size_y = backgroundSprite.getTexture().getSize().y;
    
    backgroundSprite.setOrigin({size_x/2, size_y/2});
    backgroundSprite.setPosition({window_w/2, window_h/2});
}

void Homescreen::updateButton(Mouse &mouse){
    playButton   .update(mouse);
    settingButton.update(mouse);
    exitButton   .update(mouse);
}

void Homescreen::updateScreenState(){
    if (playButton   .onRelease) nextState = screenState::GameMenu;
    if (settingButton.onRelease) nextState = screenState::Settings;
    if (exitButton   .onRelease) nextState = screenState::Exit;
}

void Homescreen::drawButton(){
    playButton   .draw(window);
    exitButton   .draw(window);
    settingButton.draw(window);
}

void Homescreen::setBackground(){
    window.draw(backgroundSprite);
}

void Homescreen::drawGamename(){
    window.draw(Gamename);
}

void Homescreen::update(Mouse &mouse){
    mouse.update(window);
    updateButton(mouse);

    updateScreenState();
}

void Homescreen::render(){
    window.clear();
    setBackground();
    drawButton();
    drawGamename();
    window.display();
}

void Homescreen::run(){

    nextState = screenState::Homescreen;

    //mouse
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        update(mouse);
        render();
        
        if (nextState != screenState::Homescreen){
            break;
        }
    }
}