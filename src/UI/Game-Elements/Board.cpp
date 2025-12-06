#include "UI/Game-Elements/Board.hpp"

// default constructor
Board::Board(sf::Font &_font, TextureManager& _gameTexture) :
    font(_font),
    gridNum(19),
    thickness(2.f),
    position({50.f, 100.f}),
    size({750.f, 750.f}),
    textures(_gameTexture),
    boardSprite(_gameTexture["PlainWood"])

{
    // texture
    // intialize shapes
    verticalLines.  setSize({thickness, size.y});
    horizontalLines.setSize({size.x, thickness});
    intersections.  setSize({10.f, 10.f});

    boardSprite.    setPosition({10.f, 60.f});

    verticalLines.  setFillColor(sf::Color::Black);
    horizontalLines.setFillColor(sf::Color::Black);
    intersections.  setFillColor(sf::Color::Black);

    intersections.  setOrigin(intersections.getGeometricCenter());

    
    // initialize grid coordinates
    gap = size.x / (gridNum - 1);
    
    for (int i = 0; i<=gridNum; i++)
    {
        gridX[i] = position.x + i * gap;
        gridY[i] = position.y + i * gap;
    }

    // initialize labels
    sf::Text defaultText(font, "", 16);
    labelchar.assign(gridNum, defaultText);
    labelnum.assign(gridNum, defaultText);

    // set up label properties
    for (int i = 0; i < gridNum; ++i) {
        labelnum[i].setFont(font);
        labelchar[i].setFont(font);
        labelnum[i].setCharacterSize(16);
        labelnum[i].setFillColor(sf::Color::Black);
        labelchar[i].setCharacterSize(16);
        labelchar[i].setFillColor(sf::Color::Black);
        labelnum[i].setString(std::to_string(i + 1));
        labelchar[i].setString(std::string(1, 'A' + i  + (i >= 8 ? 1 : 0))); // Skip 'I'
        alignText(labelnum[i], 0.5f, 0.5f);
        alignText(labelchar[i], 0.5f, 0.5f);
    }
}

// set position of the board (top-left corner not including )
void Board::setPosition(sf::Vector2f _position) {
    _position.x-=40.f;
    _position.y-=40.f;
    position = _position;
    boardSprite.setPosition(position);
}

// draw the board
void Board::draw(sf::RenderWindow &window) {
    window.draw(boardSprite);

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
    
    if (gridNum == 19)
    {
        for (int i = 0; i<=2; i++)
        {
            for (int j = 0; j<=2; j++)
            {
                intersections.setPosition({position.x + 3*gap + 6*gap*i + 1.f, position.y + 3*gap + 6*gap*j + 1.f});
                window.draw(intersections);
            }
        }
    }
    else
    {
        int dif = (gridNum - 1)/4;
        for (int i = 0; i<=1; i++)
        {
            for (int j = 0; j<=1; j++)
            {
                intersections.setPosition({position.x + dif*gap + 2*dif*gap*i + 1.f, position.y + dif*gap + 2*dif*gap*j + 1.f});
                window.draw(intersections);
            }
        }
        intersections.setPosition({position.x + 2*dif*gap + 1.f, position.y + 2*dif*gap + 1.f});
        window.draw(intersections);
    }

    // draw labels
    for (int i = 0; i < gridNum; ++i) {
        // number labels (left side)
        labelchar[i].setPosition({gridX[i], gridY[0] - (830.f - size.x)/3});
        window.draw(labelchar[i]);
        // character labels (top side)
        labelnum[i].setPosition({gridX[0] - (830.f - size.y)/3, gridY[gridNum - i - 1]});
        window.draw(labelnum[i]);
    }

}

void Board::ChangeStyle(BoardStyle _state)
{
    sf::Color _color;
    if (_state == BoardStyle::LightWood)
    {
        boardSprite.setTexture(textures["LightWood"]);
        _color = sf::Color::Black;
        
    }
    if (_state == BoardStyle::DarkWood)
    {
        boardSprite.setTexture(textures["DarkWood"]);
        _color = sf::Color(163,152,24);
        // _color = sf::Color::Yellow;
    }

    if (_state == BoardStyle::PlainWood)
    {
        boardSprite.setTexture(textures["PlainWood"]);
        _color = sf::Color::Black;
    }
    boardSprite.setPosition({10.f, 60.f});
        verticalLines.  setFillColor(_color);
        horizontalLines.setFillColor(_color);
        intersections.  setFillColor(_color);
        for (int i = 0; i<gridNum; i++)
        {
            // std::cout<<i<<'\n';
            labelchar[i].setFillColor(_color);
            labelnum[i]. setFillColor(_color);
        }
}

void Board::changeGridSize(int _gridNum)
{
    gridNum = _gridNum;

    // change position
    if (gridNum == 19) size = {730.f, 730.f};
    else if (gridNum == 13) size = {700.f, 700.f};
    else if (gridNum == 9) size = {670.f, 670.f};
    position = {10.f + (830.f - size.x)/2, 60.f + (830.f - size.y)/2};
    // initialize grid coordinates
    gap = size.x / (gridNum - 1);
    
    for (int i = 0; i<=gridNum; i++)
    {
        gridX[i] = position.x + i * gap;
        gridY[i] = position.y + i * gap;
    }

    // verticle and horizontal lines size update
    verticalLines.  setSize({thickness, size.y});
    horizontalLines.setSize({size.x, thickness});
}