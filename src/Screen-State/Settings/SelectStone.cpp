#include "Screen-State/Settings/SelectStone.hpp"


SelectStone::SelectStone(
    sf::Font &_font, 
    sf::RenderWindow &_window,
    GameScreen &_gamescreen,
    TextureManager &_gameTexture):
    
    backButton   (_font),
    ClassicButton(_font),
    PixelButton(_font),
    window(_window),
    gamescreen(_gamescreen),
    backgroundSprite(_gameTexture["Background"])
    {
        float window_w = window.getSize().x;
        float window_h = window.getSize().y;

        //Buttons setPosition
        ClassicButton.setPosition({window_w/2, window_h/2 - 2 * space - 75.f});
        PixelButton.setPosition({window_w/2, window_h/2 - space});
        backButton.   setPosition({105.f, 50.f});

        //Buttons setSize
        ClassicButton.setSize({650.f, 75.f});
        PixelButton.setSize({650.f, 75.f});
        backButton.   setSize({200.f, 60.f});

        //Buttons setString
        ClassicButton.  setString("Classic");
        PixelButton.  setString("Pixel");
        backButton.     setString("Back");

        PixelButton.setChosen();
        gamescreen.ChangeStoneStyle(GameScreen::StoneStyle::Pixel);
        gamescreen.currentStoneStyle = GameScreen::StoneStyle::Pixel;

        float scale = window_h/backgroundSprite.getTexture().getSize().y;
        backgroundSprite.setScale({scale, scale});

        float size_x = backgroundSprite.getTexture().getSize().x;
        float size_y = backgroundSprite.getTexture().getSize().y;
        
        backgroundSprite.setOrigin({size_x/2, size_y/2});
        backgroundSprite.setPosition({window_w/2, window_h/2});
    }

void SelectStone::setBackground(){
    window.draw(backgroundSprite);
}

void SelectStone::updateButton(Mouse &mouse){
    //buttons update
    ClassicButton.update(mouse);
    PixelButton.update(mouse);
    backButton.   update(mouse);
}

void SelectStone::updateScreenState(){
    if (backButton.onRelease) nextState = screenState::Exit;
}

void SelectStone::updateStyle(){
    if (ClassicButton.onRelease)
    {
        gamescreen.ChangeStoneStyle(GameScreen::StoneStyle::Classic);
        gamescreen.currentStoneStyle = GameScreen::StoneStyle::Classic;
        ClassicButton.setChosen();        
        PixelButton.setDefaultColor();
    }
    if (PixelButton.onRelease)
    {
        gamescreen.ChangeStoneStyle(GameScreen::StoneStyle::Pixel);
        gamescreen.currentStoneStyle = GameScreen::StoneStyle::Pixel;
        PixelButton.setChosen();
        ClassicButton.setDefaultColor();        
    }
}

void SelectStone::draw(){
    backButton   .draw(window);
    ClassicButton.draw(window);
    PixelButton.draw(window);
}

void SelectStone::run(){

    nextState = screenState::SelectStone;

    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        window.clear(sf::Color(64, 64, 64));
        setBackground();

        mouse.update(window);

        updateButton(mouse);
        updateScreenState();
        updateStyle();

        draw();

        window.display();

        if (nextState != screenState::SelectStone){
            break;
        }
    }
}