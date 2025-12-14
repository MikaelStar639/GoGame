#include "Screen-State/Settings/SelectBoard.hpp"


SelectBoard::SelectBoard(
    sf::Font &_font, 
    sf::RenderWindow &_window,
    TextureManager &_gameTexture,
    Board &_board):
    
    backButton      (_font),
    DarkWoodButton(_font),
    LightWoodButton(_font),
    PlainWoodButton(_font),
    window(_window),
    board(_board),
    backgroundSprite(_gameTexture["Background"])
    {
        float window_w = window.getSize().x;
        float window_h = window.getSize().y;
        DarkWoodButton .setPosition({window_w/2, window_h/2 - 2 * space - 75.f});
        PlainWoodButton.setPosition({window_w/2, window_h/2 + space});
        LightWoodButton.setPosition({window_w/2, window_h/2 - space});
        backButton     .setPosition({105.f, 50.f});

        DarkWoodButton .setSize({650.f, 75.f});
        LightWoodButton.setSize({650.f, 75.f});
        PlainWoodButton.setSize({650.f, 75.f});
        backButton     .setSize({200.f, 60.f});

        DarkWoodButton. setString("Dark Wood");
        LightWoodButton.setString("Light Wood");
        PlainWoodButton.setString("Plain Wood");
        backButton.     setString("Back");

        float scale = window_h/backgroundSprite.getTexture().getSize().y;
        backgroundSprite.setScale({scale, scale});

        float size_x = backgroundSprite.getTexture().getSize().x;
        float size_y = backgroundSprite.getTexture().getSize().y;
        
        backgroundSprite.setOrigin({size_x/2, size_y/2});
        backgroundSprite.setPosition({window_w/2, window_h/2});

        PlainWoodButton.setChosen();
    }

void SelectBoard::setBackground(){
    window.draw(backgroundSprite);
}

void SelectBoard::updateButton(Mouse &mouse){
    //buttons update
    DarkWoodButton. update(mouse);
    LightWoodButton.update(mouse);
    PlainWoodButton.update(mouse);
    backButton.     update(mouse);
}

void SelectBoard::updateScreenState(){
    if (backButton.onRelease) nextState = screenState::Exit;
}

void SelectBoard::updateStyle(){
    if (DarkWoodButton.onRelease)
    {
        board.ChangeStyle(Board::BoardStyle::DarkWood);

        DarkWoodButton .setChosen();        
        LightWoodButton.setDefaultColor();
        PlainWoodButton.setDefaultColor();
    }
    if (LightWoodButton.onRelease)
    {
        board.ChangeStyle(Board::BoardStyle::LightWood);

        DarkWoodButton .setDefaultColor();        
        LightWoodButton.setChosen();
        PlainWoodButton.setDefaultColor();
    }
    if (PlainWoodButton.onRelease)
    {
        board.ChangeStyle(Board::BoardStyle::PlainWood);

        DarkWoodButton .setDefaultColor();        
        LightWoodButton.setDefaultColor();
        PlainWoodButton.setChosen();
    }
}

void SelectBoard::update(Mouse& mouse){
    mouse.update(window);
    updateButton(mouse);
    updateScreenState();
    updateStyle();
}

void SelectBoard::render(){
    window.clear(sf::Color(64, 64, 64));
    setBackground();
    
    backButton     .draw(window);
    DarkWoodButton .draw(window);
    LightWoodButton.draw(window);
    PlainWoodButton.draw(window);

    window.display();
}

void SelectBoard::run(){
    
    nextState = screenState::SelectBoard;
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        update(mouse);
        render();

        if (nextState != screenState::SelectBoard){
            break;
        }
    }
}