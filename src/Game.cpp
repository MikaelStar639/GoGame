#include <Game.hpp>

#include <Window-State/Homescreen.hpp>
#include <Window-State/PlayOptions.hpp>
#include <Window-State/GameScreen.hpp>
#include <Window-State/Settings/Settings.hpp>

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
    
    sf::SoundBuffer backgroundMusicBuffer("assets/sounds/BackgroundMusic.mp3");
    sf::SoundBuffer stoneSoundBuffer     ("assets/sounds/stoneMove.mp3");
    sf::SoundBuffer stoneCapturedBuffer  ("assets/sounds/boom.mp3");
    
    sf::Sound backgroundMusic(backgroundMusicBuffer);
    sf::Sound stoneSound(stoneSoundBuffer);
    sf::Sound stoneCaptureSound(stoneCapturedBuffer);

    Homescreen  homeScreen (font, window, backgroundTexture);
    PlayOptions playOptions(font, window, backgroundTexture);
    Settings    settings   (font, window, backgroundTexture, backgroundMusic, stoneSound, stoneCaptureSound);

    backgroundMusic.setLooping(true);
    backgroundMusic.play();
    

    GameScreen resume (font, window, blackStoneTexture, whiteStoneTexture, 
                                backgroundTexture, stoneSound, stoneCaptureSound);

    resume.loadGame("game.saves");
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

        if (state == windowState::PlayOptions){
            playOptions.nextState = windowState::PlayOptions;
            playOptions.run();
            state = playOptions.nextState;

            if (state != windowState::Exit)
                windowStateStack.push(state);
            else
                windowStateStack.pop();

            continue;
        }

        if (state == windowState::GameScreen){
            GameScreen gameScreen (font, window, blackStoneTexture, whiteStoneTexture, 
                                   backgroundTexture, stoneSound, stoneCaptureSound);
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
            resume.saveGame("game.saves");
            
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
    }

    resume.saveGame("game.saves");
}