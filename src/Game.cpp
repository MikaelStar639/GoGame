#include <Game.hpp>

#include <Window-State/Homescreen.hpp>
#include <Window-State/GameMenu.hpp>
#include <Window-State/GameScreen.hpp>
#include <Window-State/Settings/Settings.hpp>
#include <Window-State/Settings/SelectBoard.hpp>
#include <Window-State/Settings/SelectStone.hpp>

#include <iostream>

Game::Game() : window(sf::VideoMode({1200, 900}), "GoGame"), 
               font("assets/fonts/Monocraft.ttc"){

    windowStateStack.push({windowState::Exit});
    windowStateStack.push({windowState::Homescreen});
}

void Game::run(){
    
    sf::Texture backgroundTexture("assets/images/Background.png");
    sf::Texture BlackBoard       ("assets/images/DarkWood.png");
    sf::Texture LightBoard       ("assets/images/LightWood.png");
    sf::Texture PlainBoard       ("assets/images/PlainWood.png");
    
    sf::Texture ClassicblackStoneTexture("assets/images/BlackStone.png");
    sf::Texture ClassicwhiteStoneTexture("assets/images/WhiteStone.png");
    sf::Texture CartoonBlackStoneTexture("assets/images/PixelatedBlackStone.png");
    sf::Texture CartoonWhiteStoneTexture("assets/images/PixelatedWhiteStone.png");
    
    sf::Sprite ClassicBlackStoneSprite(ClassicblackStoneTexture);
    sf::Sprite ClassicWhiteStoneSprite(ClassicwhiteStoneTexture);
    sf::Sprite CartoonBlackStoneSprite(CartoonBlackStoneTexture);
    sf::Sprite CartoonWhiteStoneSprite(CartoonWhiteStoneTexture);
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::SoundBuffer backgroundMusicBuffer("assets/sounds/BackgroundMusic.mp3");
    sf::SoundBuffer stoneSoundBuffer     ("assets/sounds/stoneMove.mp3");
    sf::SoundBuffer stoneCapturedBuffer  ("assets/sounds/boom.mp3");
    
    sf::Sound backgroundMusic(backgroundMusicBuffer);
    sf::Sound stoneSound(stoneSoundBuffer);
    sf::Sound stoneCaptureSound(stoneCapturedBuffer);

    Board board(font, LightBoard, BlackBoard, PlainBoard);

    Homescreen  homeScreen (font, window, backgroundSprite);
    GameMenu    GameMenu(font, window, backgroundSprite);
    Settings    settings   (font, window, backgroundSprite, backgroundMusic, stoneSound, stoneCaptureSound);
    SelectBoard selectBoard(font, window, board, backgroundSprite, backgroundMusic);

    backgroundMusic.setLooping(true);
    // backgroundMusic.play();
    
    GameScreen gameScreen(font, window,
         ClassicBlackStoneSprite, ClassicWhiteStoneSprite,
        CartoonBlackStoneSprite, CartoonWhiteStoneSprite,
                                    backgroundSprite, board, stoneSound, stoneCaptureSound);

    SelectStone selectStone(font, window, gameScreen, backgroundSprite, backgroundMusic);
    
    
    while (window.isOpen()){
        handleEvent(window);
        assert(!windowStateStack.empty());
        windowState state = windowStateStack.top();

        if (state == windowState::Exit){
            window.close();
            break;
        }

        if (state == windowState::Homescreen){
            homeScreen.nextState = windowState::Homescreen;
            homeScreen.run();
            state = homeScreen.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::GameMenu){
            GameMenu.nextState = windowState::GameMenu;
            GameMenu.run();

            if (GameMenu.loadGame == true){
                GameMenu.loadGame = false;
                gameScreen.loadGame("game.saves");
            }
            if (GameMenu.saveGame == true){
                gameScreen.saveGame("game.saves");
                GameMenu.saveGame = false;
                GameMenu.nextState = windowState::GameMenu;
            }

            state = GameMenu.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::NewGame){
            gameScreen.reset();
            gameScreen.canNotLoad = false;
            gameScreen.nextState = windowState::GameScreen;
            gameScreen.run();
            
            state = gameScreen.nextState;
            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::Resume){
            if (gameScreen.canNotLoad){
                windowStateStack.pop();
                state = windowStateStack.top();
                continue;
            }
            
            gameScreen.nextState = windowState::GameScreen;
            gameScreen.run();
            
            state = gameScreen.nextState;
            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::Settings){
            settings.nextState = windowState::Settings;
            settings.run();
            state = settings.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::SelectBoard){
            selectBoard.nextState = windowState::SelectBoard;
            selectBoard.run();
            state = selectBoard.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::SelectStone){
            selectStone.nextState = windowState::SelectStone;
            selectStone.run();
            state = selectStone.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }
        
    }
}