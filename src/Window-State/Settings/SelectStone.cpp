#include "Window-State/Settings/SelectStone.hpp"


SelectStone::SelectStone(
    sf::Font &_font, 
    sf::RenderWindow &_window,
    GameScreen &_gamescreen,
    sf::Sprite &_BackgroundTexture,
    sf::Sound &_BackgroundMusic):
    
    backButton   (_font),
    ClassicButton(_font),
    CartoonButton(_font),
    window(_window),
    gamescreen(_gamescreen),
    BackgroundSprite(_BackgroundTexture),
    BackgroundMusic(_BackgroundMusic)
    {
        ClassicButton.setChosen();
    }


void SelectStone::setBackground(sf::Sprite &backgroundSprite){

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

void SelectStone::updateButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    ClassicButton.setPosition({window_w/2, window_h/2 - 2 * space - 75.f});
    CartoonButton.setPosition({window_w/2, window_h/2 - space});
    backButton.   setPosition({105.f, 50.f});

    //Buttons setSize
    ClassicButton.  setSize({650.f, 75.f});
    CartoonButton. setSize({650.f, 75.f});
    backButton.      setSize({200.f, 60.f});

    //Buttons setString
    ClassicButton.  setString("Classic");
    CartoonButton.  setString("Pixel");
    backButton.     setString("Back");

    //buttons update
    ClassicButton. update(mouse);
    CartoonButton.update(mouse);
    backButton.     update(mouse);


    //check if any button is clicked
    if (ClassicButton.onRelease)
    {
        gamescreen.ChangeStoneStyle(GameScreen::StoneStyle::Classic);
        ClassicButton.setChosen();        
        CartoonButton.setDefaultColor();
    }
    if (CartoonButton.onRelease)
    {
        gamescreen.ChangeStoneStyle(GameScreen::StoneStyle::Cartoon);
        CartoonButton.setChosen();
        ClassicButton.setDefaultColor();        
    }
    if (backButton.onRelease)
    {
        nextState = Game::screenState::Exit;
    }
}


void SelectStone::draw(){
    backButton   .draw(window);
    ClassicButton.draw(window);
    CartoonButton.draw(window);
}

void SelectStone::run(){
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        window.clear(sf::Color(64, 64, 64));
        setBackground(BackgroundSprite);

        mouse.update(window);

        updateButton(mouse);

        draw();

        window.display();

        if (nextState != Game::screenState::SelectStone){
            break;
        }
    }
}