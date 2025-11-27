#pragma once

#include "UI/Button.hpp"
#include "UI/Slider/Slider.hpp"
#include "SFML/Audio.hpp"
#include "ScreenState.hpp"
#include "Assets-Manager/AssetsManager.hpp"

class Settings{
private:
    Button backButton;
    Button stoneStyleButton;
    Button boardStyleButton;
    Slider soundSlider;
    Slider musicSlider;

    sf::Sprite &BackgroundSprite;

    SoundManager& gameSound;

    sf::RenderWindow &window;
    
    const float space = 75.f;

    void setBackground(sf::Sprite &backgroundSprite);
    void updateButton(Mouse &mouse);
    void updateSlider(Mouse &mouse);
    void draw();

public:
    Settings(sf::Font &font, sf::RenderWindow &window, sf::Sprite &BackgroundSprite, SoundManager &gameSound);
    screenState nextState = screenState::Settings;
    void run();
};