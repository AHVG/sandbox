#include <iostream>
#include "Grid.h"

Grid::Grid()
{
    for(int line = 0; line < GRID_SIZE; line++)
        for(int column = 0; column < GRID_SIZE; column++)
            m_cells[line][column] = new Vacuum(sf::Vector2i(column, line));
}

Grid::~Grid()
{
    for(int line = 0; line < GRID_SIZE; line++)
        for(int column = 0; column < GRID_SIZE; column++)
            delete m_cells[line][column];
}

bool Grid::isOnGrid(const sf::Vector2i &position) const
{
    if(position.x <= -1 || GRID_SIZE <= position.x ||
       position.y <= -1 || GRID_SIZE <= position.y)
        return false;
    return true;
}

Element **Grid::getCell(const sf::Vector2i &position)
{
    if(isOnGrid(position))
        return &m_cells[position.y][position.x];
    return nullptr;
}

void Grid::addElement(const sf::Vector2i &position, const int &type)
{
    if(isOnGrid(position))
    {
        if(type == Element::VACUUM)
        {
            delete m_cells[position.y][position.x];
            m_cells[position.y][position.x] = new Vacuum(position);
        }
        else if(getCellType(position) == Element::VACUUM)
        {
            delete m_cells[position.y][position.x];

            if(type == Element::SAND)
                m_cells[position.y][position.x] = new Sand(position);
            else if(type == Element::WATER)
                m_cells[position.y][position.x] = new Water(position);
            else if(type == Element::STONE)
                m_cells[position.y][position.x] = new Stone(position);
            else if(type == Element::VACUUM)
                m_cells[position.y][position.x] = new Vacuum(position);
        }
    }
}

void Grid::addElementBlock(const sf::Vector2i &position, const int &size, const int &type)
{
    for(int line = int(-size/2); line <= int(size/2); line++)
        for(int column = int(-size/2); column <= int(size/2); column++)
            addElement(sf::Vector2i(position.x+column, position.y+line), type);
}

int Grid::getCellType(const sf::Vector2i &position)
{
    if(isOnGrid(position))
        return m_cells[position.y][position.x]->getType();
    return -1;
}

void Grid::toogle(const sf::Vector2i position1, const sf::Vector2i position2)
{
    if(isOnGrid(position1) && isOnGrid(position2))
    {
        Element *cellAux = m_cells[position1.y][position1.x];
        m_cells[position1.y][position1.x] = m_cells[position2.y][position2.x];
        m_cells[position2.y][position2.x] = cellAux;
        m_cells[position1.y][position1.x]->setPosition(position1);
        m_cells[position2.y][position2.x]->setPosition(position2);
        m_cells[position1.y][position1.x]->m_moved = true;
        m_cells[position2.y][position2.x]->m_moved = true;
    }
}

void Grid::update()
{
    if(clock.getElapsedTime().asSeconds() > REFRESH_RATE)
    {
        for(int line = 0; line < GRID_SIZE; line++)
            for(int column = 0; column < GRID_SIZE; column++)
                    if(!m_cells[line][column]->m_updated)
                        m_cells[line][column]->update(this);

        for(int line = 0; line < GRID_SIZE; line++)
            for(int column = 0; column < GRID_SIZE; column++)
                    m_cells[line][column]->reset();

        clock.restart();
    }
}

void Grid::draw(sf::RenderWindow &window)
{
    for(int line = 0; line < GRID_SIZE; line++)
        for(int column = 0; column < GRID_SIZE; column++)
                m_cells[line][column]->draw(window);
}

