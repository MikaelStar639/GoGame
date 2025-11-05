#include "UI/Game-Elements/Board.hpp"
#include <string>
#include <SFML/Graphics.hpp>



// default constructor

Board::Board(const sf::Font &font) :
    gridNum(19),
    thickness(2.f),
    position({0.f, 0.f}),
    size({750.f, 750.f})
{
    boardShape.     setSize(size);
    verticalLines.  setSize({thickness, size.y});
    horizontalLines.setSize({size.x, thickness});

    boardShape.setPosition(position);
    boardShape.setOutlineThickness(40.f);
    
    boardShape.     setOutlineColor(sf::Color(216, 159, 107));
    boardShape.     setFillColor(sf::Color(216, 159, 107));
    verticalLines  .setFillColor(sf::Color::Black);
    horizontalLines.setFillColor(sf::Color::Black);

    intersections.setSize({10.f, 10.f});
    intersections.setFillColor(sf::Color::Black);
    for (int i = 0; i < 19; ++i) {
        labelnum[i].setFont(font);
        labelchar[i].setFont(font);
        labelnum[i].setCharacterSize(16);
        labelnum[i].setFillColor(sf::Color::Black);
        labelchar[i].setCharacterSize(16);
        labelchar[i].setFillColor(sf::Color::Black);
        labelnum[i].setString(std::to_string(i + 1));
        labelchar[i].setString(std::string(1, 'A' + i));
    }

}


void Board::setPos(sf::Vector2f _position) {
    position = _position;
    boardShape.setPosition(position);
}

void Board::draw(sf::RenderWindow &window) {
    window.draw(boardShape);

    float gap = size.x / (gridNum + 1);
    // draw vertical lines
    for (int i = 0; i < gridNum; ++i) {
        verticalLines.setPosition({position.x + i * gap , position.y});
        window.draw(verticalLines);
    }
    // draw horizontal lines
    for (int i = 0; i < gridNum; ++i) {
        horizontalLines.setPosition({position.x, position.y + i * gap});
        window.draw(horizontalLines);
    }
    // draw intersections

    // draw labels

}