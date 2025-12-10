#include "UI/InfoBox.hpp"

InfoBox::InfoBox(sf::Font &font) : text(font), Info(font) {}

void InfoBox::setPosition(sf::Vector2f _position){
    position = _position;
}

void InfoBox::setSize(sf::Vector2f _size){
    size = _size;
}

void InfoBox::setText(std::string str){
    text.setString(str);
}

void InfoBox::setState(std::string str){
    Info.setString(str);
}

void InfoBox::draw(sf::RenderWindow &window){
    shape.setSize(size, radius);
    shape.setPosition(position);
    shape.setColor(sf::Color(40, 40, 40));
    shape.draw(window);

    text.setFillColor(sf::Color(64, 160, 200));
    text.setCharacterSize(size.y * text_scale);
    text.setPosition(position);
    alignText(text, 1.1f, text_align_v);
    window.draw(text);
    
    Info.setCharacterSize(size.y * text_scale);
    Info.setPosition(position);
    alignText(Info, -.025f, text_align_v);
    window.draw(Info);
}