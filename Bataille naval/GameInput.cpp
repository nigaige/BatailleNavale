#include "Utils.h"

GameInput::GameInput(){
    leftClick_ = false;
    rightClick_ = false;
    x_ = 0;
    y_ = 0;

    mouseX_ = 0;
    mouseY_ = 0;

    currentGrid_ = -1;

}
void GameInput::windowInput(){ 
    if (currentGrid_ == 1) {
        x_ = (mouseX_ - PLAYER_1_GRID_POSX) / SLOT_SIZE_X;//convert to grid coord
        y_ = (mouseY_ - PLAYER_1_GRID_POSY) / SLOT_SIZE_Y;
    }
    else if (currentGrid_ == 2) {
        x_ = (mouseX_ - PLAYER_2_GRID_POSX) / SLOT_SIZE_X;//convert to grid coord
        y_ = (mouseY_ - PLAYER_2_GRID_POSY) / SLOT_SIZE_Y;

    }
    else {
        x_ = -1;
        y_ = -1;

    }
    std::cout << "X:" + std::to_string(x_) + "Y:" + std::to_string(y_) << std::endl;

}

void GameInput::mousePos(sf::RenderWindow* window){
    mouseX_ = sf::Mouse::getPosition(*window).x;
    mouseY_ = sf::Mouse::getPosition(*window).y;
}

void GameInput::checkCurrentGrid(){
    currentGrid_ = -1;
    if (mouseX_ > PLAYER_1_GRID_POSX &&
        mouseX_<PLAYER_1_GRID_POSX + GRID_SIZE_X * SLOT_SIZE_X &&
        mouseY_ >  PLAYER_1_GRID_POSY &&
        mouseY_ < PLAYER_1_GRID_POSY + GRID_SIZE_Y * SLOT_SIZE_Y) currentGrid_ = 1;
    if (mouseX_ > PLAYER_2_GRID_POSX &&
        mouseX_<PLAYER_2_GRID_POSX + GRID_SIZE_X * SLOT_SIZE_X &&
        mouseY_ >  PLAYER_2_GRID_POSY &&
        mouseY_ < PLAYER_2_GRID_POSY + GRID_SIZE_Y * SLOT_SIZE_Y) currentGrid_ = 2;
}
