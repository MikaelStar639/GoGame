#pragma once

#include "UI/Button.hpp"
#include "UI/RoundRectShape.hpp"
#include "Screen-State/ScreenState.hpp"
#include "Assets-Manager/TextureManager.hpp"

class Homescreen : public Screen{
private:
    Button playButton;
    Button settingButton;
    Button exitButton;

    sf::Sprite backgroundSprite;

    sf::Text         Gamename;
    sf::RenderWindow &window;

    void setBackground();
    void updateButton(Mouse &mouse);
    void updateScreenState();
    void drawButton();
    void drawGamename();
    void update(Mouse &mouse);
    void render();

public:

    Homescreen(sf::Font &font, sf::RenderWindow &window, TextureManager& textureManager);
    void run();
};