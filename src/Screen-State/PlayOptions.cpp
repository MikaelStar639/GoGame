#include "Screen-State/PlayOptions.hpp"


PlayOptions::PlayOptions(sf::Font &font, sf::RenderWindow &_window, TextureManager &textures, GameScreen &_gameScreen) : 
    pvpButton (font),
    pvbButton (font),
    backButton(font),
    playButton(font),
    button9x9 (font),
    button13x13(font),
    button19x19(font),
    chooseModeText(font),
    chooseSizeText(font),
    backgroundSprite(textures["Background"]),
    window(_window), 
    gameScreen(_gameScreen){
        pvpButton.  setString("Two Player - One Device");
        pvbButton.  setString("Player vs Bot  ");
        playButton. setString("Play");
        button9x9 . setString("9 x 9");
        button13x13.setString("13 x 13");
        button19x19.setString("19 x 19");
        backButton. setString("Back");

        pvpButton.setChosen();
        button19x19.setChosen();

        chooseModeText.setString("Choose game mode");
        chooseModeText.setFillColor(sf::Color::White);
        chooseModeText.setOutlineThickness(3.f);
        chooseModeText.setOutlineColor(sf::Color::Black);
        chooseModeText.setCharacterSize(60);
        alignText(chooseModeText, 0.5f, 0.6f);

        
        chooseSizeText.setString("Choose board size");
        chooseSizeText.setCharacterSize(60);
        chooseSizeText.setFillColor(sf::Color::White);
        chooseSizeText.setOutlineThickness(3.f);
        chooseSizeText.setOutlineColor(sf::Color::Black);
        alignText(chooseSizeText, 0.5f, 0.6f);
    }

void PlayOptions::updateButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    float space = 75.f;
    
    pvpButton. setPosition({window_w/2, window_h/5});
    pvbButton. setPosition({window_w/2, window_h/5 + 1.5f*space});
    button9x9 .setPosition({window_w/2, window_h/5 + space * 4.5f});
    button13x13.setPosition({window_w/2, window_h/5 + space * 6});
    button19x19.setPosition({window_w/2, window_h/5 + space * 7.5f});
    backButton.setPosition({105.f, 50.f});
    playButton.setPosition({window_w - 150.f, window_h - 80.f});

    //Buttons setSize
    pvpButton. setSize({650.f, 75.f});
    pvbButton. setSize({650.f, 75.f});
    backButton.setSize({200.f, 60.f});
    playButton.setSize({200.f, 60.f});
    button9x9 .setSize({650.f, 75.f});
    button13x13.setSize({650.f, 75.f});
    button19x19.setSize({650.f, 75.f});

    //Text setPosition
    chooseModeText.setPosition({window_w/2, window_h/5 - 70.f});
    chooseSizeText.setPosition({window_w/2, window_h/5 + space*4.5f - 70.f});

    //buttons update
    pvpButton. update(mouse);
    pvbButton. update(mouse);
    backButton.update(mouse);
    playButton.update(mouse);
    button9x9 .update(mouse);
    button13x13.update(mouse);
    button19x19.update(mouse);
}

void PlayOptions::updateScreenState(){
    if (backButton.onRelease) nextState = screenState::Exit;
    if (playButton.onRelease) nextState = screenState::GameScreen;

    if (pvpButton .onRelease)
    {
        gameScreen.isAIMode = false;
        pvpButton.setChosen();
        pvbButton.setDefaultColor();
    }
    if (pvbButton .onRelease)
    {
        gameScreen.isAIMode = true;
        pvbButton.setChosen();
        pvpButton.setDefaultColor();
    }
    
    if (button9x9 .onRelease){
        button9x9 .setChosen();
        button13x13.setDefaultColor();
        button19x19.setDefaultColor();
        gameScreen.changeBoardSize(9);
    }
    if (button13x13.onRelease){
        button13x13.setChosen();
        button9x9 .setDefaultColor();
        button19x19.setDefaultColor();
        gameScreen.changeBoardSize(13);
    }
    if (button19x19.onRelease){
        button19x19.setChosen();
        button9x9 .setDefaultColor();
        button13x13.setDefaultColor();
        gameScreen.changeBoardSize(19);
    }
}

void PlayOptions::drawButton(){
    pvpButton. draw(window);
    pvbButton. draw(window);
    backButton.draw(window);
    playButton.draw(window);
    button9x9 .draw(window);
    button13x13.draw(window);
    button19x19.draw(window);
    window.draw(chooseModeText);
    window.draw(chooseSizeText);
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