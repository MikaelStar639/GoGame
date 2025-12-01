#include "Screen-State/GameMenu.hpp"


GameMenu::GameMenu(sf::Font &font, sf::RenderWindow &_window, TextureManager &_gameTexture, GameScreen &_gameScreen) : 
    newGameButton  (font),
    continueButton (font),
    loadGameButton (font),
    saveGameButton (font),
    backButton     (font),
    backgroundSprite(_gameTexture["Background"]),
    window(_window),
    gameScreen(_gameScreen){
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
}

void GameMenu::updateGameScreen(){
    if (newGameButton. onRelease) gameScreen.reset();
    if (saveGameButton.onRelease) gameScreen.saveGame("game.saves");
    if (loadGameButton.onRelease) gameScreen.loadGame("game.saves");
}

void GameMenu::updateScreenState(){
    if (newGameButton. onRelease) nextState = screenState::PlayOptions;
    if (continueButton.onRelease) nextState = screenState::GameScreen;
    if (loadGameButton.onRelease) nextState = screenState::GameScreen;
    if (backButton.    onRelease) nextState = screenState::Exit;
}

void GameMenu::drawButton(){
    newGameButton. draw(window);
    continueButton.draw(window);
    saveGameButton.draw(window);
    loadGameButton.draw(window);
    backButton    .draw(window);
}

void GameMenu::setBackground(){

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

    nextState = screenState::GameMenu;
    
    //mouse
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        //Background
        window.clear();
        setBackground();

        //update button
        mouse.update(window);
        updateButton(mouse);

        //update Screenstate & GameScreen
        updateGameScreen();
        updateScreenState();

        drawButton();
        window.display();
        
        //if the state is not GameMenu (some button was clicked)
        if (nextState != screenState::GameMenu){
            break;
        }
    }
}