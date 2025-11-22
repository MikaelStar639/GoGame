#include "Screen-State/GameMenu.hpp"


GameMenu::GameMenu(sf::Font &font, sf::RenderWindow &_window, sf::Sprite &BackgroundTexture) : 
    newGameButton  (font),
    continueButton (font),
    loadGameButton (font),
    saveGameButton (font),
    backButton     (font),
    BackgroundSprite(BackgroundTexture),
    window(_window){
        newGameButton. setString("New Game");
        continueButton.setString("Continue");
        saveGameButton.setString("Save Game");
        loadGameButton.setString("Load Game");
        backButton.    setString("Back");
}

void GameMenu::updateButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    float space = 60.f;
    
    newGameButton. setPosition({window_w/2, window_h/2 - 3 * space});
    continueButton.setPosition({window_w/2, window_h/2 - space});
    saveGameButton.setPosition({window_w/2, window_h/2 + space});
    loadGameButton.setPosition({window_w/2, window_h/2 + 3 * space});
    backButton.    setPosition({105.f, 50.f});

    //Buttons setSize
    newGameButton. setSize({650.f, 75.f});
    continueButton.setSize({650.f, 75.f});
    saveGameButton.setSize({650.f, 75.f});
    loadGameButton.setSize({650.f, 75.f});
    backButton.    setSize({200.f, 60.f});

    //buttons update
    newGameButton .update(mouse);
    continueButton.update(mouse);
    saveGameButton.update(mouse);
    loadGameButton.update(mouse);
    backButton    .update(mouse);

    //check if any button is clicked
    if (newGameButton .onRelease) nextState = Game::screenState::NewGame;
    if (continueButton.onRelease) nextState = Game::screenState::Resume;
    if (saveGameButton.onRelease) nextState = Game::screenState::Exit, saveGame = true;
    if (loadGameButton.onRelease) nextState = Game::screenState::Resume, loadGame = true;
    if (backButton.    onRelease) nextState = Game::screenState::Exit;
}

void GameMenu::drawButton(){
    newGameButton. draw(window);
    continueButton.draw(window);
    saveGameButton.draw(window);
    loadGameButton.draw(window);
    backButton    .draw(window);
}

void GameMenu::setBackground(sf::Sprite &backgroundSprite){

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

void GameMenu::run(){

    //mouse
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        //Background
        window.clear();
        setBackground(BackgroundSprite);

        //update
        mouse.update(window);
        updateButton(mouse);

        //just draw :v
        drawButton();
        window.display();
        
        //if the state is not GameMenu (some button was clicked)
        if (nextState != Game::screenState::GameMenu){
            break;
        }
    }
}