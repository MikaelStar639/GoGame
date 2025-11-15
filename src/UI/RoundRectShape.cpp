#include "UI/RoundRectShape.hpp"


// Default constructor
RoundRectShape::RoundRectShape() :
    size({100.f, 50.f}), 
    radius(10.f),
    position({0.f, 0.f}),
    color(sf::Color::Blue)
{
    setSize(size, radius); 
    setPosition(position);
    setColor(color);
}

//Initialize Constructor 
RoundRectShape::RoundRectShape(
    sf::Vector2f init_size, 
    float init_radius, 
    sf::Vector2f init_pos, 
    sf::Color init_color
) :
    size(init_size),
    radius(init_radius),
    position(init_pos),
    color(init_color)
{
    setSize(init_size, init_radius);
    setPosition(init_pos);
    setColor(init_color);
}

void RoundRectShape::setSize(sf::Vector2f _size, float _radius)
    {
        size = _size;
        radius = _radius;
        rect1.setSize({_size.x - 2*_radius, _size.y});
        rect2.setSize({_size.x, _size.y - 2*_radius});
        rect1.setOrigin(rect1.getGeometricCenter());
        rect2.setOrigin(rect2.getGeometricCenter());
        
        for (int i = 0; i<=3; i++)
        {
            circle[i].setRadius(radius);
            circle[i].setOrigin(circle[i].getGeometricCenter());
        }
    }

void RoundRectShape:: setPosition(sf::Vector2f _position)
{
    position = _position;
    rect1.setPosition(_position);
    rect2.setPosition(_position);
    
    float halfx = (size.x - 2*radius)/2;
    float halfy = (size.y - 2*radius)/2;
    circle[0].setPosition({_position.x - halfx, _position.y - halfy});
    circle[1].setPosition({_position.x + halfx, _position.y - halfy});
    circle[2].setPosition({_position.x - halfx, _position.y + halfy});
    circle[3].setPosition({_position.x + halfx, _position.y + halfy});   
}

void RoundRectShape::setColor(sf::Color _color)
{
    color = _color;
    rect1.setFillColor(color);
    rect2.setFillColor(color);
    for(int i = 0; i<=3; i++) circle[i].setFillColor(color);
}

void RoundRectShape::draw(sf::RenderWindow &window)
{
    window.draw(rect1);
    window.draw(rect2);
    for(int i = 0; i<=3; i++) window.draw(circle[i]);
}

bool RoundRectShape::isContain(sf::Vector2f pos)
{
    if (rect1.getGlobalBounds().contains(pos))
        return true;
    
    if (rect2.getGlobalBounds().contains(pos))
        return true;
    
    for (int i = 0; i <= 3; ++i){
        if (circle[i].getGlobalBounds().contains(pos)){
            return true;
        }
    }

    return false;
}

