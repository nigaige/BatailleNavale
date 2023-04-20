#include <SFML/Graphics.hpp>


#ifdef _DEBUG
#include <crtdbg.h>
#include <Windows.h>
#endif

#include "Utils.h";

int main()
{
#ifdef _DEBUG
    _CrtMemState memStateInit;
    _CrtMemCheckpoint(&memStateInit);
#endif


    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
#ifdef _DEBUG
    _CrtMemState memStateEnd, memStateDiff;
    _CrtMemCheckpoint(&memStateEnd);
    if (_CrtMemDifference(&memStateDiff, &memStateInit, &memStateEnd))
    {
        MessageBoxA(NULL, "MEMORY LEAKS", "DISCLAIMER", 0);
    }
#endif 
}