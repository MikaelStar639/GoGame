#include "Ultil.hpp"

// to edit text
void alignText(sf::Text &text, float horizontal, float vertical){
    sf::FloatRect bounds = text.getLocalBounds();

    float x = bounds.position.x + bounds.size.x * horizontal;
    float y = text.getCharacterSize() * vertical;

    text.setOrigin({x, y});
}

void handleEvent(sf::RenderWindow &window){
    while (auto event = window.pollEvent()){
        if (event->is<sf::Event::Closed>()){
            window.close();
            break;
        }
        if (event->is<sf::Event::Resized>()){
            sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
            window.setView(view);
        }
    }
}