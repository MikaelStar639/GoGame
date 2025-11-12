#include "Window-State/GameScreen.hpp"
// #include <iostream>

GameScreen::GameScreen(sf::Font &_font, sf::RenderWindow &_window, 
                sf::Texture &BlackTexture, sf::Texture &WhiteTexture,
                sf::Texture &BackgroundTexture) : 

    backButton  (_font),
    redoButton  (_font),
    undoButton  (_font),
    passButton  (_font),
    resignButton(_font),
    window      (_window),
    board       (_font),
    BackgroundSprite(BackgroundTexture)
    {

    //Button String
    backButton.  setString("Back");
    redoButton.  setString("Redo");
    undoButton.  setString("Undo");
    passButton.  setString("Pass");
    resignButton.setString("Resign");

    //vector:
    
    grid.resize(19);
    for (int y = 0; y < 19; ++y){
        grid[y].reserve(19);
        for (int x = 0; x < 19; ++x){
            grid[y].emplace_back(BlackTexture, WhiteTexture, 
                sf::Vector2f(board.gridX[x], board.gridY[18 - y]));
        }
    }
}

void GameScreen::setBackground(sf::Sprite &backgroundSprite){

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

void GameScreen::drawBoard(){
    board.draw(window);
}

void GameScreen::setBoard(Board &_board){
    board = _board;
}

void GameScreen::updateFeatureButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    //Buttons setPosition
    backButton.setPosition({85.f, 30.f});

    //Buttons setSize
    backButton.setSize({150.f, 50.f});

    //Buttons update
    backButton.update(mouse);

    //check button state
    if (backButton.onRelease) nextState = Game::windowState::Exit;
}

void GameScreen::updateGameButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    float space = 80.f;

    //Buttons setPosition
    redoButton  .setPosition({window_w * 6/7, window_h/2 - 2 * space - 75.f});
    undoButton  .setPosition({window_w * 6/7, window_h/2 - space});
    passButton  .setPosition({window_w * 6/7, window_h/2 + space});  
    resignButton.setPosition({window_w * 6/7, window_h/2 + 2 * space + 75.f});
    
    //Buttons setSize
    redoButton  .setSize({300.f, 75.f});
    undoButton  .setSize({300.f, 75.f});
    passButton  .setSize({300.f, 75.f});
    resignButton.setSize({300.f, 75.f});

    //Buttons update
    redoButton  .update(mouse);
    undoButton  .update(mouse);
    passButton  .update(mouse);  
    resignButton.update(mouse);

    //check button state
    if (redoButton  .onRelease);
    if (undoButton  .onRelease);
    if (passButton  .onRelease);
    if (resignButton.onRelease);
}

GameScreen::Cordinate GameScreen::to_cord(sf::Vector2f position){
    float fy = (position.y - board.gridY[0])/board.gap;
    float fx = (position.x - board.gridX[0])/board.gap;

    int j = std::round(fy);
    int i = std::round(fx);

    if (std::min(j, i) < 0 || 19 <= std::max(i, j)){
        return {-1, -1};
    }

    float py = board.gridY[j];
    float px = board.gridX[i];

    sf::Vector2f diff = position - sf::Vector2f(px, py);
    float dist2 = diff.x * diff.x + diff.y * diff.y;

    float radius = board.gap/2;
    if (dist2 <= radius * radius){
        return {18 - j, i};
    }

    return {-1, -1};
}

void GameScreen::updateStone(Mouse &mouse){
    auto [cy, cx] = to_cord(mouse.position);
    if (cy == -1) return;
    
    Stone &overStone = grid[cy][cx];
    overStone.update(mouse);

    if (overStone.onRelease == false){
        if (overStone.state == Stone::State::empty){
            overStone.isOver = true;

            if (gameState.turn == GameState::Turn::black){
                overStone.color = Stone::Color::black;
            }
            else{
                overStone.color = Stone::Color::white;
            }
        }
    }
    else{
        if (overStone.state == Stone::State::empty){
            if (gameState.isIllegal(cy, cx, gameState.turn)){
                return;
            }
            if (gameState.turn == GameState::Turn::black){
                overStone.setState(Stone::State::black);
            }
            else{
                overStone.setState(Stone::State::white);
            }
            gameState.addStone(cy, cx);
            gameState.RemoveCapturedStones(grid);
            newTurn = true;
        }
    }

}

void GameScreen::updateGameState(){
    if (newTurn == true){
        if (gameState.turn == GameState::Turn::black){
            gameState.turn = GameState::Turn::white;
        }
        else{
            gameState.turn = GameState::Turn::black;
        }

        newTurn = false;
    }
}

void GameScreen::drawButton(){
    backButton  .draw(window);
    redoButton  .draw(window);
    undoButton  .draw(window);
    passButton  .draw(window);  
    resignButton.draw(window);
}

void GameScreen::drawStone(){
    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            grid[y][x].draw(window);
        }
    }
}

void GameScreen::run(){

    //mouse
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        //background
        window.clear(sf::Color(64, 64, 64));
        setBackground(BackgroundSprite);

        //mouse
        mouse.update(window);
        
        //update elements
        updateFeatureButton(mouse);
        updateGameButton(mouse);
        updateStone(mouse);
        updateGameState();

        //draw
        drawBoard();
        drawButton();
        drawStone();

        window.display();

        if (nextState != Game::windowState::GameScreen){
            break;
        }
    }
}