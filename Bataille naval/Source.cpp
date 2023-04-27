#include "Utils.h"

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

    sf::RenderWindow window(sf::VideoMode(WINDOWSIZE_X, WINDOWSIZE_Y), "Bataille navale!!");
    window.setKeyRepeatEnabled(false);
    
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    input.windowInput(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, PLAYER_1_GRID_POS);
                    gm.game(input);
                }

                else if (event.mouseButton.button == sf::Mouse::Right) {
                    input.swapClick();
                }
            }
        }
        gm.drawGame(window);
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