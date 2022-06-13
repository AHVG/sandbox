#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class Key
{
    private:

    public:

    enum KeyState{PRESSED, RELEASED};

    Key();
    Key(const Key &);
    ~Key();

    const Key &operator=(const Key &k);

    int m_previousState;
    int m_currentState;

};

class Keyboard
{

    private:

    public:

    std::map<sf::Keyboard::Key, Key> m_keys;

    Keyboard();
    ~Keyboard();

    void initialize();
    void update();
    bool click(sf::Keyboard::Key key);

};

#endif // KEYBOARD_H_INCLUDED
