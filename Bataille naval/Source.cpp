#include <SFML/Graphics.hpp>


#ifdef _DEBUG
#include <crtdbg.h>
#include <Windows.h>
#endif

#include "Utils.h";
#include <iostream>

//compile pr 

int main()
{
#ifdef _DEBUG
    _CrtMemState memStateInit;
    _CrtMemCheckpoint(&memStateInit);
#endif


    GameManager gm;
    gm.init();
    GameInput input;

    Map map;

    sf::RenderWindow window(sf::VideoMode(WINDOWSIZE_X, WINDOWSIZE_Y), "Bataille navale");
    sf::VertexArray grid = map.drawGrid(&window);
   
    
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            input.windowInput(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
            gm.game(input);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            input.swapClick();
        }

        window.clear();
        window.draw(grid);
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