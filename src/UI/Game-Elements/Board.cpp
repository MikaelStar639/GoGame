#include "UI/Game-Elements/Board.hpp"
#include <string>
#include <SFML/Graphics.hpp>



// default constructor

Board::Board() :
    gridNum(19),
    thickness(2.f),
    position({50.f, 100.f}),
    size({750.f, 750.f})
{
    boardShape.     setSize(size);
    verticalLines.  setSize({thickness, size.y});
    horizontalLines.setSize({size.x, thickness});
    intersections.  setSize({10.f, 10.f});

    boardShape.setPosition(position);
    boardShape.setOutlineThickness(40.f);
    
    boardShape.     setFillColor(sf::Color(216, 159, 107));
    verticalLines  .setFillColor(sf::Color::Black);
    horizontalLines.setFillColor(sf::Color::Black);
    intersections.  setFillColor(sf::Color::Black);
    boardShape.     setOutlineColor(sf::Color(216, 159, 107));

    intersections.  setOrigin(intersections.getGeometricCenter());

    gap = size.x / (gridNum - 1);

    for (int i = 0; i<=19; i++)
    {
        Gridx[i] = position.x + i * gap;
        Gridy[i] = position.y + i * gap;
    }

    // for (int i = 0; i < 19; ++i) {
    //     labelnum[i].setFont(font);
    //     labelchar[i].setFont(font);
    //     labelnum[i].setCharacterSize(16);
    //     labelnum[i].setFillColor(sf::Color::Black);
    //     labelchar[i].setCharacterSize(16);
    //     labelchar[i].setFillColor(sf::Color::Black);
    //     labelnum[i].setString(std::to_string(i + 1));
    //     labelchar[i].setString(std::string(1, 'A' + i));
    // }

}


void Board::setPos(sf::Vector2f _position) {
    position = _position;
    boardShape.setPosition(position);
}

void Board::draw(sf::RenderWindow &window) {
    window.draw(boardShape);

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
    
    for (int i = 0; i<=2; i++)
    {
        for (int j = 0; j<=2; j++)
        {
            intersections.setPosition({position.x + 3*gap + 6*gap*i, position.y + 3*gap + 6*gap*j});
            window.draw(intersections);
        }
    }

    // draw labels

}