#include "Constants.h"
#include "Program.h"


Program::Program() : m_window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Cellular V 2.0"), m_type(Element::STONE),
m_cursor_size(3){}

Program::~Program(){}

void Program::initialize()
{
    m_keyboard.initialize();
}

void Program::run()
{
    while(m_window.isOpen())
    {
        handleInput();
        handleEvent();
        handleUpdate();
        handleRendering();
    }
}

void Program::handleInput()
{
    bool mouse = false;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        mouse = true;

    if(m_keyboard.click(sf::Keyboard::Num0))
        m_type = Element::VACUUM;
    else if(m_keyboard.click(sf::Keyboard::Num1))
        m_type = Element::SAND;
    else if(m_keyboard.click(sf::Keyboard::Num2))
        m_type = Element::WATER;
    else if(m_keyboard.click(sf::Keyboard::Num3))
        m_type = Element::STONE;
    else if(m_keyboard.click(sf::Keyboard::Hyphen))
    {
        m_cursor_size -= 2;
        if(m_cursor_size < 3)
            m_cursor_size = 1;
    }
    else if(m_keyboard.click(sf::Keyboard::Equal))
    {
        m_cursor_size += 2;
        if(m_cursor_size > 11)
            m_cursor_size = 11;
    }

    if (mouse)
    {
        sf::Vector2i position = sf::Mouse::getPosition(m_window);
        position /= CELL_SIZE;
        position = sf::Vector2i(position.x * 2, GRID_SIZE) - position;
        grid.addElementBlock(position, m_cursor_size, m_type);
    }
}

void Program::handleEvent()
{
    while (m_window.pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Program::handleUpdate()
{
    grid.update();
    m_keyboard.update();
}

void Program::handleRendering()
{
    m_window.clear();
    grid.draw(m_window);
    m_window.display();
}
