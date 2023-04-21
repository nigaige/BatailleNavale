#include "Utils.h"

GameInput::GameInput(){
    rightClick_ = false;
    x_ = 0;
    y_ = 0;
}
void GameInput::windowInput(int x, int y, int WinX, int winY ){ 
    x_ = x/(WINDOWSIZE_X/10);
    y_ = y/(WINDOWSIZE_Y/10);
}