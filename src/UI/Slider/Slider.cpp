#include "UI/Slider/Slider.hpp"

Slider::Slider(std::string _str, sf::Font &font, 
               sf::Vector2f _size,sf::Vector2f _position) : 
    size(_size), position(_position),
    thumb(_position.x - 50.f, _position.y, _size.x/2),
    track(thumb),
    text(font, _str) {}

Slider::Slider(sf::Font &font) : track(thumb), text(font){}

void Slider::update(Mouse &mouse){
    thumb.update(mouse);
    track.update(thumb);
    value = 100.f * thumb.value/thumb.maxValue;
}

void Slider::setPosition(sf::Vector2f _position){
    thumb.setPosition({_position.x - 50.f, _position.y});
    position = _position;
}

void Slider::setSize(sf::Vector2f _size){
    thumb.setLength(_size.x/2);
    track.setThumb(thumb);
    size = _size;
}

void Slider::setString(std::string str){
    text.setString(str);
}


void Slider::draw(sf::RenderWindow &window){
    bound.setSize(size, radius);
    bound.setPosition(position);
    bound.setColor(sf::Color(40, 40, 40));
    bound.draw(window);

    text.setFillColor(sf::Color(200, 200, 200));
    text.setCharacterSize(size.y * text_scale);
    text.setPosition(position);
    alignText(text, 2.f, text_align_v);

    window.draw(text);
    track.draw(window);
    thumb.draw(window);
}