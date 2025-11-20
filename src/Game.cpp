#include <Game.hpp>

#include <Window-State/Homescreen.hpp>
#include <Window-State/GameMenu.hpp>
#include <Window-State/GameScreen.hpp>
#include <Window-State/Settings/Settings.hpp>
#include <Window-State/Settings/SelectBoard.hpp>

#include <iostream>

Game::Game() : window(sf::VideoMode({1200, 900}), "GoGame"), 
               font("assets/fonts/Monocraft.ttc"){

    windowStateStack.push({windowState::Exit});
    windowStateStack.push({windowState::Homescreen});
}

void Game::run(){
    
    sf::Texture backgroundTexture("assets/images/Background.png");
    sf::Texture blackStoneTexture("assets/images/BlackStone.png");
    sf::Texture whiteStoneTexture("assets/images/WhiteStone.png");
    sf::Texture BlackBoard       ("assets/images/DarkWood.png");
    sf::Texture LightBoard       ("assets/images/LightWood.png");
    sf::Texture PlainBoard       ("assets/images/PlainWood.png");

    sf::Sprite BlackStoneSprite(blackStoneTexture);
    sf::Sprite WhiteStoneSprite(whiteStoneTexture);

    sf::SoundBuffer backgroundMusicBuffer("assets/sounds/BackgroundMusic.mp3");
    sf::SoundBuffer stoneSoundBuffer     ("assets/sounds/stoneMove.mp3");
    sf::SoundBuffer stoneCapturedBuffer  ("assets/sounds/boom.mp3");
    
    sf::Sound backgroundMusic(backgroundMusicBuffer);
    sf::Sound stoneSound(stoneSoundBuffer);
    sf::Sound stoneCaptureSound(stoneCapturedBuffer);

    Board board(font, LightBoard, BlackBoard, PlainBoard);

    Homescreen  homeScreen (font, window, backgroundTexture);
    GameMenu    GameMenu(font, window, backgroundTexture);
    Settings    settings   (font, window, backgroundTexture, backgroundMusic, stoneSound, stoneCaptureSound);
    SelectBoard selectBoard(font, window, board, backgroundTexture, backgroundMusic);

    backgroundMusic.setLooping(true);
    // backgroundMusic.play();
    

    GameScreen resume(font, window, BlackStoneSprite, WhiteStoneSprite, 
                                backgroundTexture, board, stoneSound, stoneCaptureSound);

    
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
            if (GameMenu.loadGame == true) resume.loadGame("game.saves");
            if (GameMenu.saveGame == true) resume.saveGame("game.saves");
            GameMenu.loadGame = false;

            state = GameMenu.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::GameScreen){
            GameScreen gameScreen (font, window,BlackStoneSprite , WhiteStoneSprite, 
                                   backgroundTexture, board, stoneSound, stoneCaptureSound);
            gameScreen.nextState = windowState::GameScreen;
            gameScreen.run();
            
            gameScreen.copyTo(resume);

            state = gameScreen.nextState;
            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::Resume){
            if (resume.canNotLoad){
                windowStateStack.pop();
                state = windowStateStack.top();
                continue;
            }
            
            resume.nextState = windowState::GameScreen;
            resume.run();
            
            state = resume.nextState;
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
    }
}