#pragma once

#include "UI/Game-Elements/Board.hpp"
#include "UI/Button.hpp"
#include "Screen-State/ScreenState.hpp"
#include "SFML/Audio.hpp"
#include "Assets-Manager/TextureManager.hpp"

class SelectBoard: public Screen{
private:
    Button backButton;
    Button LightWoodButton;
    Button DarkWoodButton;
    Button PlainWoodButton;

    Board &board;

    sf::Sprite backgroundSprite;

    sf::RenderWindow &window;
    
    const float space = 75.f;
    
    void setBackground();
    void updateButton(Mouse &mouse);
    void updateScreenState();
    void updateStyle();

    void update(Mouse &mouse);
    void render();
public:
    SelectBoard(sf::Font &font, sf::RenderWindow &window, 
        TextureManager& gameTexture, Board &board);
    
    void run();
};