#include "Screen-State/Settings/SelectBoard.hpp"


SelectBoard::SelectBoard(
    sf::Font &_font, 
    sf::RenderWindow &_window,
    Board &_board,
    sf::Sprite &_BackgroundTexture,
    sf::Sound &_BackgroundMusic):
    
    backButton      (_font),
    DarkWoodButton(_font),
    LightWoodButton(_font),
    PlainWoodButton(_font),
    window(_window),
    board(_board),
    BackgroundSprite(_BackgroundTexture),
    BackgroundMusic(_BackgroundMusic)
    {
        PlainWoodButton.setChosen();
    }


void SelectBoard::setBackground(sf::Sprite &backgroundSprite){

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

void SelectBoard::updateButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    DarkWoodButton.setPosition({window_w/2, window_h/2 - 2 * space - 75.f});
    LightWoodButton.setPosition({window_w/2, window_h/2 - space});
    PlainWoodButton.setPosition({window_w/2, window_h/2 + space});
    backButton.      setPosition({105.f, 50.f});

    //Buttons setSize
    DarkWoodButton.  setSize({650.f, 75.f});
    LightWoodButton. setSize({650.f, 75.f});
    PlainWoodButton. setSize({650.f, 75.f});
    backButton.      setSize({200.f, 60.f});

    //Buttons setString
    DarkWoodButton. setString("Dark Wood");
    LightWoodButton.setString("Light Wood");
    PlainWoodButton.setString("Plain Wood");
    backButton      .setString("Back");

    //buttons update
    DarkWoodButton. update(mouse);
    LightWoodButton.update(mouse);
    PlainWoodButton.update(mouse);
    backButton.     update(mouse);


    //check if any button is clicked
    if (DarkWoodButton.onRelease)
    {
        board.ChangeStyle(Board::BoardStyle::DarkWood);
        DarkWoodButton.setChosen();        
        LightWoodButton.setDefaultColor();
        PlainWoodButton.setDefaultColor();
    }
    if (LightWoodButton.onRelease)
    {
        board.ChangeStyle(Board::BoardStyle::LightWood);
        DarkWoodButton.setDefaultColor();        
        LightWoodButton.setChosen();
        PlainWoodButton.setDefaultColor();
    }
    if (PlainWoodButton.onRelease)
    {
        board.ChangeStyle(Board::BoardStyle::PlainWood);
        DarkWoodButton.setDefaultColor();        
        LightWoodButton.setDefaultColor();
        PlainWoodButton.setChosen();
    }
    if (backButton.onRelease)     nextState = Game::screenState::Exit;
}


void SelectBoard::draw(){
    backButton      .draw(window);
    DarkWoodButton.draw(window);
    LightWoodButton.draw(window);
    PlainWoodButton.draw(window);
}

void SelectBoard::run(){
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        window.clear(sf::Color(64, 64, 64));
        setBackground(BackgroundSprite);

        mouse.update(window);

        updateButton(mouse);

        draw();

        window.display();

        if (nextState != Game::screenState::SelectBoard){
            break;
        }
    }
}