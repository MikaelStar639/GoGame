#include "UI/Button.hpp"

Button::Button(const sf::Font &font) : text(font) {}

void Button::setPosition(sf::Vector2f _position){
    position = _position;
}

void Button::setSize(sf::Vector2f _size){
    size = _size;
}

void Button::setString(std::string _string){
    string = _string;
}

void Button::setColor(std::array<sf::Color, 6> colorList){
    sf::Color default_shape = colorList[0];
    sf::Color default_text  = colorList[1];
    
    sf::Color over_shape    = colorList[2];
    sf::Color over_text     = colorList[3];

    sf::Color pressed_shape = colorList[4];
    sf::Color pressed_text  = colorList[5];
}

void Button::update(Mouse &mouse){
    //reset states
    onPress   = false;
    onRelease = false;

    //mouse
    if (shape.getGlobalBounds().contains(mouse.position)){
        if (mouse.onPress){
            //first click
            onPress   = true;
            isPressed = true;
        }
        if (mouse.onRelease && isPressed){
            //first release
            onRelease = true;
        }

        if (mouse.isPressed && isPressed){
            //if already clicked inside the button
            isPressed = true;
        }

        isOver = true;
    }
    else{
        isOver    = false;
        isPressed = false;
    }
    
    if (!mouse.isPressed){
        isPressed = false;
    }
}

//draw
void Button::draw(sf::RenderWindow& window){

    //shape
    shape.setSize(size);
    shape.setOrigin(shape.getGeometricCenter());
    shape.setPosition(position);
    window.draw(shape);

    //text
    text.setString(string);
    text.setCharacterSize(size.y * text_scale);
    text.setPosition(position);
    alignText(text, 0.5f, text_align_v);

    //color 
    if (isPressed){
        shape.setFillColor(pressed_shape);
        text.setFillColor(pressed_text);
    }
    else if (isOver){
        shape.setFillColor(over_shape);
        text.setFillColor(over_text);
    }
    else{
        shape.setFillColor(default_shape);
        text.setFillColor(default_text);
    }

    window.draw(text);
}
