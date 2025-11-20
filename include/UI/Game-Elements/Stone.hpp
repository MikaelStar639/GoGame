#pragma once
#include <SFML/Graphics.hpp>

#include <Input/Mouse.hpp>
class Stone{    

private:
    sf::Sprite BlackStoneSprite;
    sf::Sprite WhiteStoneSprite;

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

    State state = State::empty;
    Color color = Color::black;
    
    //empty state:
    bool isOver    = false;
    bool isPressed = false;
    bool onPress   = false;
    bool onRelease = false;

    bool isContain(sf::Vector2f _position);
    void update(Mouse &mouse);

    Stone(sf::Sprite &_blackStoneTexture, sf::Sprite &_whiteStoneTexture,
          sf::Vector2f _position);

    
    void setPosition(sf::Vector2f pos);

    // visual info
    sf::Vector2f position;
    void setState(State state);
    void draw(sf::RenderWindow &window);
    void ChangeSprite(sf::Sprite &newSpriteBlack, sf::Sprite &newSpriteWhite);
};