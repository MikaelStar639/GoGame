#include <SFML/Graphics.hpp>

class Stone{    

private:
    sf::Sprite BlackstoneSprite;
    sf::Sprite WhitestoneSprite;

public:
    enum class stoneState{
        empty,
        black,
        white
    };
    // board info
    stoneState state = stoneState::empty;
    Stone(sf::Sprite &_BlackstoneSprite, sf::Sprite &_WhitestoneSprite, sf::Vector2f _pos);
    void setPosition(sf::Vector2f pos);
    
    // visual info
    sf::Vector2f position;
    void setState(stoneState state);
    void draw(sf::RenderWindow &window);
};