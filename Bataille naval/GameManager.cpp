#include "Utils.h"

void GameManager::init(){
	turnCount = 0;
	currentPlayer = 0;
	delete player[0];//In case the function is called again to prevent memory leak
	delete player[1];
	player[0] = new Player();
	player[1] = new Player();
	player[0]->placeShip();
	player[1]->placeShip();


}

void GameManager::turn(int player)
{

}

GameManager::GameManager(){
	player[0] = nullptr;
	player[1] = nullptr;
}

GameManager::~GameManager()
{
}
