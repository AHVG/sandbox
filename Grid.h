#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <array>
#include "Constants.h"
#include "Elements.h"

class Element;

class Grid
{

    private:

    std::array<std::array<Element *, 100>, 100> m_cells;
    sf::Clock clock;
    const float REFRESH_RATE = 0.016;

    public:

    Grid();
    ~Grid();

    bool isOnGrid(const sf::Vector2i &position) const;
    Element **getCell(const sf::Vector2i &position);

    void addElement(const sf::Vector2i &position, const int &type);
    void addElementBlock(const sf::Vector2i &position, const int &size, const int &type);
    int getCellType(const sf::Vector2i &position);
    void toogle(const sf::Vector2i position1, const sf::Vector2i position2);

    void update();
    void draw(sf::RenderWindow &window);
};

#endif // GRID_H_INCLUDED
