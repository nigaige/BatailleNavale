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

    Map map;

    sf::RenderWindow window(sf::VideoMode(WINDOWSIZE_X, WINDOWSIZE_Y), "Bataille navale!!");
    window.setKeyRepeatEnabled(false);
    
    while (window.isOpen()){


        gm.readInput(&window);
        gm.game();
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