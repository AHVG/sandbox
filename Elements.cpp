#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Elements.h"
#include "Constants.h"

//======================================================================

Element::Element(const sf::Vector2i &position) : m_updated(false), m_moved(false), m_position(position){std::srand(time(NULL));}
Element::~Element(){}

void Element::reset(){m_updated = false; m_moved = false;}

void Element::setPosition(const sf::Vector2i &position){m_position = position;}

//======================================================================

Vacuum::Vacuum(const sf::Vector2i &position) : Element(position){}
Vacuum::~Vacuum(){}

int Vacuum::getType() const {return Element::VACUUM;}

void Vacuum::update(Grid *grid)
{
    m_updated = true;
}

void Vacuum::draw(sf::RenderWindow &window)
{
    sf::Vector2f position = sf::Vector2f(m_position.x*CELL_SIZE, (GRID_SIZE - m_position.y - 1)*CELL_SIZE);
    sf::RectangleShape square;
    square.setFillColor(sf::Color::White);
    square.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
    square.setPosition(position);
    window.draw(square);
}

//======================================================================

Sand::Sand(const sf::Vector2i &position) : Element(position){}
Sand::~Sand(){}

int Sand::getType() const {return Element::SAND;}

void Sand::update(Grid *grid)
{
    sf::Vector2i downCell = sf::Vector2i(m_position.x, m_position.y - 1);
    sf::Vector2i leftCell = sf::Vector2i(m_position.x - 1, m_position.y - 1);
    sf::Vector2i rightCell = sf::Vector2i(m_position.x + 1, m_position.y - 1);

    if(grid->getCellType(downCell) == Element::WATER)
    {
        if(!((*(grid->getCell(downCell)))->m_moved))
            grid->toogle(m_position, downCell);
    }
    else if(grid->getCellType(leftCell) == Element::WATER)
    {
        if(!((*(grid->getCell(leftCell)))->m_moved))
            grid->toogle(m_position, leftCell);
    }
    else if(grid->getCellType(rightCell) == Element::WATER)
    {
        if(!((*(grid->getCell(rightCell)))->m_moved))
            grid->toogle(m_position, rightCell);
    }
    else if(grid->getCellType(downCell) == Element::VACUUM)
        grid->toogle(m_position, downCell);
    else if(grid->getCellType(leftCell) == Element::VACUUM)
        grid->toogle(m_position, leftCell);
    else if(grid->getCellType(rightCell) == Element::VACUUM)
        grid->toogle(m_position, rightCell);

    m_updated = true;
}

void Sand::draw(sf::RenderWindow &window)
{
    sf::Vector2f position = sf::Vector2f(m_position.x*CELL_SIZE, (GRID_SIZE - m_position.y - 1)*CELL_SIZE);
    sf::RectangleShape square;
    square.setFillColor(sf::Color(250,190,9));
    square.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
    square.setPosition(position);
    window.draw(square);
}

//======================================================================

Water::Water(const sf::Vector2i &position) : Element(position){}
Water::~Water(){}

int Water::getType() const {return Element::WATER;}

void Water::update(Grid *grid)
{
    sf::Vector2i downCell = sf::Vector2i(m_position.x, m_position.y - 1);
    sf::Vector2i leftCell = sf::Vector2i(m_position.x - 1, m_position.y - 1);
    sf::Vector2i rightCell = sf::Vector2i(m_position.x + 1, m_position.y - 1);
    sf::Vector2i targetCell = sf::Vector2i(m_position.x, m_position.y);
    targetCell.x += (std::rand()%2 ? -1 : 1);

    if(grid->getCellType(downCell) == Element::VACUUM)
        grid->toogle(m_position, downCell);
    else if(grid->getCellType(leftCell ) == Element::VACUUM)
        grid->toogle(m_position, leftCell);
    else if(grid->getCellType(rightCell) == Element::VACUUM)
        grid->toogle(m_position, rightCell);
    else if(grid->getCellType(targetCell) == Element::VACUUM)
        grid->toogle(m_position, targetCell);

    m_updated = true;
}

void Water::draw(sf::RenderWindow &window)
{
    sf::Vector2f position = sf::Vector2f(m_position.x*CELL_SIZE, (GRID_SIZE - m_position.y - 1)*CELL_SIZE);
    sf::RectangleShape square;
    square.setFillColor(sf::Color::Blue);
    square.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
    square.setPosition(position);
    window.draw(square);
}

//======================================================================

Stone::Stone(const sf::Vector2i &position) : Element(position){}
Stone::~Stone(){}

int Stone::getType() const {return Element::STONE;}

void Stone::update(Grid *grid)
{
    m_updated = true;
}

void Stone::draw(sf::RenderWindow &window)
{
    sf::Vector2f position = sf::Vector2f(m_position.x*CELL_SIZE, (GRID_SIZE - m_position.y - 1)*CELL_SIZE);
    sf::RectangleShape square;
    square.setFillColor(sf::Color(100,100,100));
    square.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
    square.setPosition(position);
    window.draw(square);
}

//======================================================================
