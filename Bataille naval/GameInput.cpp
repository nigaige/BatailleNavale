#include "Utils.h"

GameInput::GameInput(){
    leftClick_ = false;
    rightClick_ = false;
    x_ = 0;
    y_ = 0;

    mouseX_ = 0;
    mouseY_ = 0;

    CurrentGrid_ = -1;

}
void GameInput::windowInput(int x, int y, int gridX, int gridY ){ 
    if ((x > gridX && x < gridX + GRID_SIZE_X * SLOT_SIZE_X) &&
        (y > gridY && y < gridY + GRID_SIZE_Y * SLOT_SIZE_Y)) {//Click is in the grid
        x_ = (x - gridX) / SLOT_SIZE_X;//convert to grid coord
        y_ = (y - gridY) / SLOT_SIZE_Y;
    }
    else {
        x_ = -1;
        y_ = -1;
    }
}

void GameInput::mousePos(sf::RenderWindow* window){
    mouseX_ = sf::Mouse::getPosition(*window).x;
    mouseY_ = sf::Mouse::getPosition(*window).y;
}

void GameInput::CurrentGrid(){
    CurrentGrid_ = -1;
    if (mouseX_ > PLAYER_1_GRID_POSX &&
        mouseX_<PLAYER_1_GRID_POSX + GRID_SIZE_X * SLOT_SIZE_X &&
        mouseY_ >  PLAYER_1_GRID_POSY &&
        mouseY_ < PLAYER_1_GRID_POSY + GRID_SIZE_Y * SLOT_SIZE_Y) CurrentGrid_ = 1;
    if (mouseX_ > PLAYER_2_GRID_POSX &&
        mouseX_<PLAYER_2_GRID_POSX + GRID_SIZE_X * SLOT_SIZE_X &&
        mouseY_ >  PLAYER_2_GRID_POSY &&
        mouseY_ < PLAYER_2_GRID_POSY + GRID_SIZE_Y * SLOT_SIZE_Y) CurrentGrid_ = 2;
}
