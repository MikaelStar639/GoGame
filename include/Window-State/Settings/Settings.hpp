#pragma once

#include "Game.hpp"
#include "UI/Button.hpp"
#include "UI/Slider/Slider.hpp"

class Settings{
private:
    Button backButton;
    Button stoneStyleButton;
    Button boardStyleButton;
    Slider soundSlider;
    Slider musicSlider;

    sf::Sprite &BackgroundSprite;
    sf::Sound &BackgroundMusic;
    sf::Sound &stoneSound;
    sf::Sound &stoneCaptureSound;

    sf::RenderWindow &window;
    
    const float space = 75.f;

public:
    Settings(sf::Font &font, sf::RenderWindow &window, 
             sf::Sprite &BackgroundSprite,
             sf::Sound &BackgroundMusic, 
             sf::Sound &stoneSound,
             sf::Sound &stoneCaptureSound);
    
    Game::windowState nextState = Game::windowState::Settings;
    
    void setBackground(sf::Sprite &backgroundSprite);
    void updateButton(Mouse &mouse);
    void updateSlider(Mouse &mouse);
    void draw();
    void run();
};