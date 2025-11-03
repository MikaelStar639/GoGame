#include "UI/Button.hpp"

void alignText(sf::Text &text, float horizontal, float vertical){
    sf::FloatRect bounds = text.getLocalBounds();

    float x = bounds.position.x + bounds.size.x * horizontal;
    float y = text.getCharacterSize() * vertical;

    text.setOrigin({x, y});
}

Button::Button(const sf::Font &font) : text(font) {}

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
