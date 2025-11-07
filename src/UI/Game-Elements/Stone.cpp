#include "UI/Game-Elements/Stone.hpp"

Stone::Stone(sf::Sprite &_BlackstoneSprite, sf::Sprite &_WhitestoneSprite, sf::Vector2f _pos) : 
    BlackstoneSprite(_BlackstoneSprite),
    WhitestoneSprite(_WhitestoneSprite),
    position(_pos)
{
    sf::FloatRect bounds = BlackstoneSprite.getLocalBounds();
    BlackstoneSprite.setOrigin(bounds.size.componentWiseMul({0.5f, 0.5f}));
    bounds = WhitestoneSprite.getLocalBounds();
    WhitestoneSprite.setOrigin(bounds.size.componentWiseMul({0.5f, 0.5f}));
    BlackstoneSprite.setPosition(position);
    WhitestoneSprite.setPosition(position);
    BlackstoneSprite.setScale({0.04f, 0.04f});
    WhitestoneSprite.setScale({0.04f, 0.04f});
}

void Stone::setPosition(sf::Vector2f pos){
    position = pos;
    BlackstoneSprite.setPosition(position);
    WhitestoneSprite.setPosition(position);
}

void Stone::setState(stoneState _nextState)
{
    state = _nextState;
}

void Stone::draw(sf::RenderWindow &window)
{
    if (state == Stone::stoneState::black) window.draw(BlackstoneSprite);
    if (state == Stone::stoneState::white) window.draw(WhitestoneSprite); 
}
