#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Keyboard.h"

class Program
{

    private:

    sf::RenderWindow m_window;
    sf::Event m_event;
    Keyboard m_keyboard;
    int m_type;
    int m_cursor_size;

    Grid grid;

    void handleUpdate();
    void handleEvent();
    void handleInput();
    void handleRendering();

    public:

    Program();
    ~Program();

    void initialize();
    void run();

};

#endif // PROGRAM_H_INCLUDED
