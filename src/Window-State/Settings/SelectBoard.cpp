#include "Window-State/Settings/SelectBoard.hpp"
#include <iostream>


SelectBoard::SelectBoard(
    sf::Font &_font, 
    sf::RenderWindow &_window,
    Board &_board,
    sf::Texture &_BackgroundTexture,
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
        PlainWoodButton.default_text = sf::Color::Yellow;
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
        DarkWoodButton.default_text = sf::Color::Yellow;
        LightWoodButton.default_text = sf::Color(200, 200, 200);
        PlainWoodButton.default_text = sf::Color(200, 200, 200);
    }
    if (LightWoodButton.onRelease)
    {
        board.ChangeStyle(Board::BoardStyle::LightWood);
        DarkWoodButton.default_text = sf::Color(200, 200, 200);
        LightWoodButton.default_text = sf::Color::Yellow;
        PlainWoodButton.default_text = sf::Color(200, 200, 200);
    }
    if (PlainWoodButton.onRelease)
    {
        board.ChangeStyle(Board::BoardStyle::PlainWood);
        DarkWoodButton.default_text = sf::Color(200, 200, 200);
        LightWoodButton.default_text = sf::Color(200, 200, 200);
        PlainWoodButton.default_text = sf::Color::Yellow;
    }
    if (backButton.onRelease)     nextState = Game::windowState::Exit;
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

        if (nextState != Game::windowState::SelectBoard){
            break;
        }
    }
}