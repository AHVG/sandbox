#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Grid.h"

class Grid;

class Element
{
    private:

    protected:

    public:

    enum types {VACUUM, SAND, WATER, STONE};

    bool m_updated;
    bool m_moved;
    sf::Vector2i m_position;

    Element(const sf::Vector2i &position);
    virtual ~Element();

    virtual void reset();
    virtual void setPosition(const sf::Vector2i &position);
    virtual int getType() const = 0;
    virtual void update(Grid *grid) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

class Vacuum : public Element
{
    private:

    protected:

    public:

    Vacuum(const sf::Vector2i &position);
    ~Vacuum();

    virtual int getType() const override;
    virtual void update(Grid *grid) override;
    virtual void draw(sf::RenderWindow &window) override;
};

class Sand : public Element
{
    private:

    protected:

    public:

    Sand(const sf::Vector2i &position);
    ~Sand();

    virtual int getType() const override;
    virtual void update(Grid *grid) override;
    virtual void draw(sf::RenderWindow &window) override;
};

class Water : public Element
{
    private:

    protected:

    public:

    Water(const sf::Vector2i &position);
    ~Water();

    virtual int getType() const override;
    virtual void update(Grid *grid) override;
    virtual void draw(sf::RenderWindow &window) override;
};

class Stone : public Element
{
    private:

    protected:

    public:

    Stone(const sf::Vector2i &position);
    ~Stone();

    virtual int getType() const override;
    virtual void update(Grid *grid) override;
    virtual void draw(sf::RenderWindow &window) override;
};

#endif // ELEMENTS_H_INCLUDED
