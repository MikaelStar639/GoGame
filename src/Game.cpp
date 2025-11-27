#include <Game.hpp>


Game::Game() : window(sf::VideoMode({1200, 900}), "GoGame", sf::Style::Default ^ sf::Style::Resize), 
               font("assets/fonts/Monocraft.ttc"){

    screenStateStack.push({screenState::Exit});
    screenStateStack.push({screenState::Homescreen});
}

void Game::run(){
    
    //* Sprite
    sf::Sprite backgroundSprite(gameTexture["BackGround"]);

    //* Sounds
    sf::Sound stoneSound       (gameSound["StoneMove"]);
    sf::Sound stoneCaptureSound(gameSound["StoneCapture"]);
    sf::Sound endGameSound     (gameSound["Boom"]);

    //* Board
    Board board(font);

    Homescreen  homeScreen (font, window, backgroundSprite);
    GameMenu    GameMenu   (font, window, backgroundSprite);
    Settings    settings   (font, window, backgroundSprite, gameSound);
    SelectBoard selectBoard(font, window, board, backgroundSprite, gameSound["BackgroundMusic"]);
    GameScreen  gameScreen (font, window, backgroundSprite, board, stoneSound, stoneCaptureSound, endGameSound);
    
    //* Stone Selector
    SelectStone selectStone(font, window, gameScreen, backgroundSprite, gameSound["BackgroundMusic"]);
    
    //* Sound Default
    gameSound["BackgroundMusic"].setLooping(true);
    gameSound["BackgroundMusic"].setVolume(75);
    gameSound["BackgroundMusic"].setVolume(75);
    stoneSound.setVolume(75);
    stoneCaptureSound.setVolume(75);
    endGameSound.setVolume(75);
    gameSound["BackgroundMusic"].play();

    //* Window Icon
    sf::Image icon("assets/images/PixelatedBlackStone.png");
    window.setIcon(icon);
    
    while (window.isOpen()){
        handleEvent(window);
        assert(!screenStateStack.empty());
        screenState state = screenStateStack.top();

        if (state == screenState::Exit){
            window.close();
            break;
        }

        if (state == screenState::Homescreen){
            homeScreen.nextState = screenState::Homescreen;
            homeScreen.run();
            state = homeScreen.nextState;

            if (state != screenState::Exit)
                screenStateStack.push(state);
            else
                screenStateStack.pop();

            continue;
        }

        if (state == screenState::GameMenu){
            GameMenu.nextState = screenState::GameMenu;
            GameMenu.run();

            if (GameMenu.loadGame == true){
                GameMenu.loadGame = false;
                gameScreen.loadGame("game.saves");
            }
            if (GameMenu.saveGame == true){
                gameScreen.saveGame("game.saves");
                GameMenu.saveGame = false;
                GameMenu.nextState = screenState::GameMenu;
            }

            state = GameMenu.nextState;

            if (state != screenState::Exit)
                screenStateStack.push(state);
            else
                screenStateStack.pop();

            continue;
        }

        if (state == screenState::NewGame){
            gameScreen.reset();
            gameScreen.canNotLoad = false;
            gameScreen.nextState = screenState::GameScreen;
            gameScreen.run();
            
            state = gameScreen.nextState;
            if (state != screenState::Exit)
                screenStateStack.push(state);
            else
                screenStateStack.pop();

            continue;
        }

        if (state == screenState::Resume){
            if (gameScreen.canNotLoad){
                screenStateStack.pop();
                state = screenStateStack.top();
                continue;
            }
            
            gameScreen.nextState = screenState::GameScreen;
            gameScreen.run();
            
            state = gameScreen.nextState;
            if (state != screenState::Exit)
                screenStateStack.push(state);
            else
                screenStateStack.pop();

            continue;
        }

        if (state == screenState::Settings){
            settings.nextState = screenState::Settings;
            settings.run();
            state = settings.nextState;

            if (state != screenState::Exit)
                screenStateStack.push(state);
            else
                screenStateStack.pop();

            continue;
        }

        if (state == screenState::SelectBoard){
            selectBoard.nextState = screenState::SelectBoard;
            selectBoard.run();
            state = selectBoard.nextState;

            if (state != screenState::Exit)
                screenStateStack.push(state);
            else
                screenStateStack.pop();

            continue;
        }

        if (state == screenState::SelectStone){
            selectStone.nextState = screenState::SelectStone;
            selectStone.run();
            state = selectStone.nextState;

            if (state != screenState::Exit)
                screenStateStack.push(state);
            else
                screenStateStack.pop();

            continue;
        }
    }
}