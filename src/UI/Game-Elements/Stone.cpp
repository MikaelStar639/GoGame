#include "UI/Game-Elements/Stone.hpp"

Stone::Stone(sf::Texture &_BlackstoneTexture, sf::Texture &_WhitestoneTexture, sf::Vector2f _pos) : 
    BlackStoneSprite(_BlackstoneTexture),
    WhiteStoneSprite(_WhitestoneTexture),
    position(_pos)
{
    sf::FloatRect bounds = BlackStoneSprite.getLocalBounds();
    BlackStoneSprite.setOrigin(bounds.size.componentWiseMul({0.5f, 0.5f}));
    bounds = WhiteStoneSprite.getLocalBounds();
    WhiteStoneSprite.setOrigin(bounds.size.componentWiseMul({0.5f, 0.5f}));
    BlackStoneSprite.setPosition(position);
    WhiteStoneSprite.setPosition(position);
    BlackStoneSprite.setScale({0.04f, 0.04f});
    WhiteStoneSprite.setScale({0.04f, 0.04f});
}

void Stone::setPosition(sf::Vector2f _position){
    position = _position;
    BlackStoneSprite.setPosition(position);
    WhiteStoneSprite.setPosition(position);
}

bool Stone::isContain(sf::Vector2f _position){
    sf::Vector2f diff = position - _position;
    float dist2 = diff.x * diff.x + diff.y * diff.y;

    float radius = 750.f/36.f;
    return dist2 <= radius * radius;
}

void Stone::update(Mouse &mouse){
        // reset states
    onPress   = false;
    onRelease = false;

    //mouse
    if (isContain(mouse.position)){
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

void Stone::setState(State _nextState)
{
    state = _nextState;
}

void Stone::draw(sf::RenderWindow &window){
    BlackStoneSprite.setPosition(position);
    WhiteStoneSprite.setPosition(position);
    if (state != State::empty){
        if (state == State::black){
            window.draw(BlackStoneSprite);
        }
        else{
            window.draw(WhiteStoneSprite);
        }
        return;
    }

    if (isOver == false) return;
    
    //it should be at the update but this one is easier to maintain
    isOver = false;
    
    if (color == Color::black){
        BlackStoneSprite.setColor(sf::Color(255, 255, 255, 128));
        window.draw(BlackStoneSprite);
        BlackStoneSprite.setColor(sf::Color(255, 255, 255, 255));
    }
    else{
        WhiteStoneSprite.setColor(sf::Color(255, 255, 255, 128));
        window.draw(WhiteStoneSprite);
        WhiteStoneSprite.setColor(sf::Color(255, 255, 255, 255));
    }
}

void Stone::ChangeSprite(sf::Texture &newBlackTexture, sf::Texture &newWhiteTexture)
{
    BlackStoneSprite.setTexture(newBlackTexture);
    WhiteStoneSprite.setTexture(newWhiteTexture);
    sf::FloatRect bounds = BlackStoneSprite.getLocalBounds();
    BlackStoneSprite.setScale({0.04f, 0.04f});
    WhiteStoneSprite.setScale({0.04f, 0.04f});
    BlackStoneSprite.setOrigin(bounds.size.componentWiseMul({0.5f, 0.5f}));
    WhiteStoneSprite.setOrigin(bounds.size.componentWiseMul({0.5f, 0.5f}));
}