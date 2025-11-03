#pragma once
#include <SFML/Graphics.hpp>

class Mouse{
public:
    //position
    sf::Vector2f position;

    //state
    bool isPressed  = false;
    bool onPress    = false;
    bool onRelease  = false;
    
    //function - update State
    void update(sf::RenderWindow& window);
};
