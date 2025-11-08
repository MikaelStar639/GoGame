#include "UI/Game-Elements/Stone.hpp"

Stone::Stone(sf::Vector2f _pos) : 
    position(_pos),
    whitestone("assets/images/WhiteStone.png"),
    blackstone("assets/images/BlackStone.png"),
    WhiteStoneSprite(whitestone),
    BlackStoneSprite(blackstone)
{
    whitestone.setSmooth(true);
    blackstone.setSmooth(true);
    sf::FloatRect bounds = BlackStoneSprite.getLocalBounds();
    BlackStoneSprite.setOrigin(bounds.size.componentWiseMul({0.5f, 0.5f}));
    bounds = WhiteStoneSprite.getLocalBounds();
    WhiteStoneSprite.setOrigin(bounds.size.componentWiseMul({0.5f, 0.5f}));
    BlackStoneSprite.setPosition(position);
    WhiteStoneSprite.setPosition(position);
    BlackStoneSprite.setScale({0.04f, 0.04f});
    WhiteStoneSprite.setScale({0.04f, 0.04f});
}

void Stone::setPosition(sf::Vector2f pos){
    position = pos;
    BlackStoneSprite.setPosition(position);
    WhiteStoneSprite.setPosition(position);
}

void Stone::setState(stoneState _nextState)
{
    state = _nextState;
}

void Stone::draw(sf::RenderWindow &window)
{
    if (state == Stone::stoneState::black) window.draw(BlackStoneSprite);
    if (state == Stone::stoneState::white) window.draw(WhiteStoneSprite); 
}


bool Stone::isContain(sf::Vector2f point){
    sf::FloatRect bounds;
    
    if (state == stoneState::black){
        bounds = BlackStoneSprite.getGlobalBounds();
    }
    else if (state == stoneState::white){
        bounds = WhiteStoneSprite.getGlobalBounds();
    }
    else{
        return false;
    }
    return bounds.contains(point);
}