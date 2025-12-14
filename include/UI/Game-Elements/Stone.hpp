#pragma once
#include <SFML/Graphics.hpp>

#include <Input/Mouse.hpp>
class Stone{  
private:
    sf::Sprite BlackStoneSprite;
    sf::Sprite WhiteStoneSprite;

    int gridNum = 19;
    sf::Vector2f position;    

public:
    enum class State{
        empty,
        black,
        white 
    };
    enum class Color{
        black,
        white
    };

    Stone(sf::Texture &_blackStoneTexture, sf::Texture &_whiteStoneTexture,
          sf::Vector2f _position);

    State state = State::empty;
    Color color = Color::black;

    float scaleRate = 0.04f;
    
    bool isOver    = false;
    bool isPressed = false;
    bool onPress   = false;
    bool onRelease = false;

    

    void update(Mouse &mouse);
    void draw(sf::RenderWindow &window);
    bool isContain(sf::Vector2f _position);
    void setPosition(sf::Vector2f pos);
    void setState(State state);
    void Scale(float newscale);
    void ChangeSprite(sf::Texture &newBlackTexure, sf::Texture &newWhiteTexture);
};