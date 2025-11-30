#include "Screen-State/GameScreen.hpp"

GameScreen::GameScreen(sf::Font &_font, sf::RenderWindow &_window, 
                TextureManager &_gameTexture, SoundManager &_gameSound,
                Board &_board) : 

    backButton  (_font),
    redoButton  (_font),
    undoButton  (_font),
    passButton  (_font),
    resetButton(_font),
    window      (_window),
    board       (_board),
    turnIndicator(_font),
    textures(_gameTexture),
    backgroundSprite(_gameTexture["Background"]),
    blackScoreBoard(_font, ScoreBoard::Player::black),
    whiteScoreBoard(_font, ScoreBoard::Player::white),
    endGameSound(_gameSound["Boom"]),
    gameState(_gameSound["StoneCapture"], _gameSound["StoneMove"]),
    endGame(_font)
    {

    //Button String
    backButton.  setString("Menu");
    redoButton.  setString("Redo");
    undoButton.  setString("Undo");
    passButton.  setString("Pass");
    resetButton.setString("Reset Game");

    //vector:
    grid.resize(19);
    Stone initStone(textures["BlackStone"], textures["WhiteStone"], sf::Vector2f(0.f, 0.f));
    for (int y = 0; y < 19; ++y){
        grid[y].reserve(19);
        for (int x = 0; x < 19; ++x){
            initStone.position = sf::Vector2f(board.gridX[x], board.gridY[18 - y]);
            grid[y].emplace_back(initStone);
        }
    }
}

void GameScreen::setBackground(){

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
}

void GameScreen::updateGameButton(Mouse &mouse){
    //window size
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;

    float space = 40.f + 75.f;

    //Buttons setPosition
    passButton  .setPosition({window_w * 6/7, window_h/2});
    undoButton  .setPosition({window_w * 6/7, window_h/2 + space});
    redoButton  .setPosition({window_w * 6/7, window_h/2 + 2 * space});  
    resetButton.setPosition({window_w * 6/7, window_h/2 + 3 * space});
    
    //Buttons setSize
    redoButton  .setSize({300.f, 75.f});
    undoButton  .setSize({300.f, 75.f});
    passButton  .setSize({300.f, 75.f});
    resetButton .setSize({300.f, 75.f});

    //Buttons update
    redoButton .update(mouse);
    undoButton .update(mouse);
    passButton .update(mouse);  
    resetButton.update(mouse);

    //Pass
    if (gameState.isEnd){
        passButton.isInvalid = true;
    }
}

Position GameScreen::to_cord(sf::Vector2f position){
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
            gameState.lastMovePass = false;
            if (gameState.turn == GameState::Turn::black){
                overStone.setState(Stone::State::black);
            }
            else{
                overStone.setState(Stone::State::white);
            }
            gameState.addStoneMove(cy, cx);
        }
    }

}

void GameScreen::updateScreenState(){
    if (backButton.onRelease) nextState = screenState::Exit;
}

void GameScreen::updateGameState(){
    if (!passButton.isInvalid && passButton.onRelease) {
        if (gameState.lastMovePass == true) {
            gameState.isEnd = true;
            endGameSound.play();
        }
        else{
            gameState.pass();
        }
        gameState.lastMovePass = true;
    }

    if (redoButton.onRelease) {
        gameState.redo();
    }
    if (undoButton.onRelease){
        gameState.undo();
    }
    
    if (resetButton.onRelease){
        reset();
    }
}

void GameScreen::drawButton(){
    backButton  .draw(window);
    redoButton  .draw(window);
    undoButton  .draw(window);
    passButton  .draw(window);  
    resetButton.draw(window);
}

void GameScreen::drawStone(){
    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            grid[y][x].draw(window);
        }
    }
}

void GameScreen::updateIndicator(){
    float window_w = window.getSize().x;
    float window_h = window.getSize().y;
    float space = 40.f + 75.f;
    turnIndicator.setSize({300.f, 75.f});
    turnIndicator.setPosition({window_w * 6/7, window_h/2 - 3 * space});
    turnIndicator.updateTurn(gameState);
}

void GameScreen::drawIndicator(){
    turnIndicator.draw(window);
}

void GameScreen::updateScoreBoard(){

    float window_w = window.getSize().x;
    float window_h = window.getSize().y;
    float space = 40.f + 75.f;

    blackScoreBoard.setSize({300.f, 75.f});
    whiteScoreBoard.setSize({300.f, 75.f});

    blackScoreBoard.setPosition({window_w * 6/7, window_h/2 - 2 * space});
    whiteScoreBoard.setPosition({window_w * 6/7, window_h/2 - space});

    gameState.getScore();
    blackScoreBoard.getScore(gameState);
    whiteScoreBoard.getScore(gameState);

    if (gameState.blackScore > gameState.whiteScore){
        blackScoreBoard.isWin = true;
        whiteScoreBoard.isWin = false;
    }
    else{
        blackScoreBoard.isWin = false;
        whiteScoreBoard.isWin = true;
    }
}

void GameScreen::drawScoreBoard(){
    blackScoreBoard.draw(window);
    whiteScoreBoard.draw(window);
}

void GameScreen::SyncStoneWithGameState(){
    for (int y = 0; y < 19; ++y){
        for (int x = 0; x < 19; ++x){
            if (gameState.grid[y][x] != grid[y][x].state){
                grid[y][x].setState(gameState.grid[y][x]);
            }
        }
    }
}

void GameScreen::reset(){
    gameState.reset();
    endGame.isClosed = endGame.isReset = false;
    passButton.isInvalid = false;
}

void GameScreen::run(){

    //mouse
    Mouse mouse;

    while (window.isOpen()){
        handleEvent(window);

        //background
        window.clear(sf::Color(64, 64, 64));
        setBackground();

        //mouse
        mouse.update(window);
        
        if (!gameState.isEnd){
            //update elements
            updateFeatureButton(mouse);
            updateGameButton(mouse);
            updateStone(mouse);
            SyncStoneWithGameState();
            updateGameState();
            updateIndicator();
            updateScoreBoard();
        }
        else{
            if (endGame.isReset){
                reset();
                continue;
            }
            if (endGame.isClosed){
                updateFeatureButton(mouse);
                updateGameButton(mouse);
                SyncStoneWithGameState();
                updateGameState();
                updateIndicator();
                updateScoreBoard();
            }
        }

        //draw
        drawBoard();
        drawButton();
        drawStone();
        drawIndicator();
        drawScoreBoard();

        if (gameState.isEnd && !endGame.isClosed){
            endGame.update(gameState);
            endGame.run(window, mouse);
        }

        updateScreenState();
        window.display();

        if (nextState != screenState::GameScreen){
            break;
        }
    }
}

void GameScreen::loadGame(std::string _address){
    gameState.load(_address);
    SyncStoneWithGameState();
}

void GameScreen::saveGame(std::string _address){
    gameState.save(_address);
}

void GameScreen::ChangeStoneStyle(StoneStyle style)
{
    for (int y = 0; y<19; y++)
    {
        for (int x = 0; x<19; x++)
        {
            if (style == StoneStyle::Classic)
                grid[y][x].ChangeSprite(textures["BlackStone"],  textures["WhiteStone"]);

            if (style == StoneStyle::Cartoon) 
                grid[y][x].ChangeSprite(textures["PixelatedBlackStone"], textures["PixelatedWhiteStone"]);
        }
    }
}