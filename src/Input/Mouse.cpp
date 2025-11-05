#include "Input/Mouse.hpp"

void Mouse::update(sf::RenderWindow& window) {
    //update position
    position = sf::Vector2f(sf::Mouse::getPosition(window));

    //reset state
    onPress    = false;
    onRelease  = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        if (!isPressed){
            //first click
            onPress = true;
        }

        isPressed = true;
    }
    else{
        if (isPressed){
            //first release
            onRelease = true;
        }

        isPressed = false;
    }
}