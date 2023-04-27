#include "Utils.h"

GameInput::GameInput(){
    rightClick_ = false;
    x_ = 0;
    y_ = 0;
}
void GameInput::windowInput(int x, int y, int gridX, int gridY ){ 
    if ((x > gridX && x < gridX + GRID_SIZE_X * SLOT_SIZE_X) &&
        (y > gridY && y < gridY + GRID_SIZE_Y * SLOT_SIZE_Y)) {
        x_ = (x - gridX) / SLOT_SIZE_X;
        y_ = (y - gridY) / SLOT_SIZE_Y;
    }
    
}