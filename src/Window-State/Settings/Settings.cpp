#include "Window-State/Settings/Settings.hpp"


Settings::Settings(
    sf::Font &_font, 
    sf::RenderWindow &_window, 
    sf::Sprite &_BackgroundTexture,
    sf::Sound &_BackgroundMusic,
    sf::Sound &_stoneSound,
    sf::Sound &_stoneCaptureSound,
    sf::Sound &_endGameSound):
    
    backButton      (_font),
    stoneStyleButton(_font),
    boardStyleButton(_font),
    window(_window),
    BackgroundSprite(_BackgroundTexture),
    BackgroundMusic(_BackgroundMusic),
    soundSlider(_font),
    musicSlider(_font),
    stoneSound(_stoneSound),
    stoneCaptureSound(_stoneCaptureSound),
    endGameSound(_endGameSound)
    {}


void Settings::setBackground(sf::Sprite &backgroundSprite){

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

void Settings::updateButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    stoneStyleButton.setPosition({window_w/2, window_h/2 - 2 * space - 75.f});
    boardStyleButton.setPosition({window_w/2, window_h/2 - space});
    backButton.      setPosition({105.f, 50.f});

    //Buttons setSize
    stoneStyleButton.setSize({650.f, 75.f});
    boardStyleButton.setSize({650.f, 75.f});
    backButton.      setSize({200.f, 60.f});

    //Buttons setString
    stoneStyleButton.setString("Stone Style");
    boardStyleButton.setString("Board Style");
    backButton      .setString("Back");

    //buttons update
    stoneStyleButton.update(mouse);
    boardStyleButton.update(mouse);
    backButton.update(mouse);

    //check if any button is clicked
    if (stoneStyleButton.onRelease) nextState = Game::windowState::SelectStone;
    if (boardStyleButton.onRelease) nextState = Game::windowState::SelectBoard;
    if (backButton.onRelease)       nextState = Game::windowState::Exit;
}

void Settings::updateSlider(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //sliders setPosition
    soundSlider.setPosition({window_w/2, window_h/2 + 2 * space + 75.f});
    musicSlider.setPosition({window_w/2, window_h/2 + space});

    //sliders setsize
    soundSlider.setSize({650.f, 75.f});
    musicSlider.setSize({650.f, 75.f});

    //setstring
    soundSlider.setString("Sound");
    musicSlider.setString("Music");

    //update
    soundSlider.update(mouse);
    musicSlider.update(mouse);

    //update sounds
    BackgroundMusic  .setVolume(musicSlider.value);
    stoneCaptureSound.setVolume(soundSlider.value);
    stoneSound       .setVolume(soundSlider.value);
    endGameSound     .setVolume(soundSlider.value);
}

void Settings::draw(){
    backButton      .draw(window);
    stoneStyleButton.draw(window);
    boardStyleButton.draw(window);
    soundSlider     .draw(window);
    musicSlider     .draw(window);
}

void Settings::run(){
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        window.clear(sf::Color(64, 64, 64));
        setBackground(BackgroundSprite);

        mouse.update(window);

        updateButton(mouse);
        updateSlider(mouse);

        draw();

        window.display();

        if (nextState != Game::windowState::Settings){
            break;
        }
    }
}