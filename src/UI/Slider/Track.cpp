#include <UI/Slider/Track.hpp>

Track::Track(Thumb& thumb):
    length(thumb.length), position({thumb.minX, thumb.y}), 
    value(1.f * thumb.value/thumb.maxValue) {}

void Track::setThumb(Thumb &thumb){
    length = thumb.length; 
    position = {thumb.minX, thumb.y};
    value = 1.f * thumb.value/thumb.maxValue;
}

void Track::update(Thumb &thumb){
    value = 1.f * thumb.value/thumb.maxValue;
}

void Track::draw(sf::RenderWindow &window){
    leftShape.setSize({value * length, 10.f});
    rightShape.setSize({(1.f - value) * length, 10.f});

    leftShape.setOrigin({0.f, 5.f});
    rightShape.setOrigin({(1.f - value) * length, 5.f});

    leftShape.setPosition(position);
    rightShape.setPosition({position.x + length, position.y});

    leftShape.setFillColor(sf::Color::Black);
    rightShape.setFillColor(sf::Color(200, 200, 200));

    window.draw(leftShape);
    window.draw(rightShape);
}