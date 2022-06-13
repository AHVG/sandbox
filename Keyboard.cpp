#include <SFML/Graphics.hpp>
#include "Keyboard.h"

std::vector<sf::Keyboard::Key> keys = {sf::Keyboard::Num0,
                                       sf::Keyboard::Num1,
                                       sf::Keyboard::Num2,
                                       sf::Keyboard::Num3,
                                       sf::Keyboard::Equal,
                                       sf::Keyboard::Hyphen,
                                       sf::Keyboard::R};

Key::Key()
{
   m_currentState = RELEASED;
   m_previousState = RELEASED;
}

Key::Key(const Key &k)
{
    *this = k;
}

Key::~Key(){}

const Key &Key::operator=(const Key &k)
{
    this->m_currentState = k.m_currentState;
    this->m_previousState = k.m_previousState;
    return *this;
}

Keyboard::Keyboard()
{}

Keyboard::~Keyboard(){}

void Keyboard::initialize()
{
    Key k;
    for(auto key : keys)
    {
        k.m_currentState = Key::RELEASED;
        k.m_previousState = Key::RELEASED;
        m_keys[key] = k;
    }
}

void Keyboard::update()
{
    for(auto key : keys)
    {
        m_keys[key].m_previousState = m_keys[key].m_currentState;
        if(sf::Keyboard::isKeyPressed(key))
            m_keys[key].m_currentState = Key::PRESSED;
        else
            m_keys[key].m_currentState = Key::RELEASED;
    }
}

bool Keyboard::click(sf::Keyboard::Key key)
{
    if(m_keys[key].m_currentState == Key::PRESSED && m_keys[key].m_previousState == Key::RELEASED)
        return true;
    return false;
}

