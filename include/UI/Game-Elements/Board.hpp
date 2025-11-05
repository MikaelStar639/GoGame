//TODO: Implement here
#include <SFML/Graphics.hpp>
#include "Ultil.hpp"

class Board {
private:
    sf::RectangleShape boardShape;
    sf::RectangleShape horizontalLines;
    sf::RectangleShape verticalLines;
    sf::RectangleShape intersections;
    // sf::Text labelnum[20];
    // sf::Text labelchar[20];
    // std::vector<sf::Text> labelnum = std::vector<sf::Text>(20);
    // std::vector<sf::Text> labelchar = std::vector<sf::Text>(20);

public:
    sf::Vector2f size;
    sf::Vector2f position;

    float thickness;
    float gap;
    int gridNum;
    float Gridx[20];
    float Gridy[20];

    // Board(const sf::Font &font);
    Board();
    void setPos(sf::Vector2f _position);
    void draw(sf::RenderWindow &window);

};