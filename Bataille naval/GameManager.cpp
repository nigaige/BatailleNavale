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


void GameManager::game(){
	init();
	while (testVictory()) {
		turn();
	}
	//currentPlayer is loser
	winner();
}

void GameManager::turn(){
	//TODO get input
	//TODO manage waiting for input when in remote	--
	int inputX = 0, inputY = 0;
	if (player[currentPlayer]->grille().shoot(inputX, inputY)) {
		player[(currentPlayer == 1) ? 0 : 1]		//otherPlayer
			->HP(player[currentPlayer]->HP() - 1);	//reduce their hp
	};
	turnCount++;
	currentPlayer = (currentPlayer == 1) ? 0 : 1;	//Swap player
}


bool GameManager::testVictory(){
	return player[currentPlayer]->HP() > 0;
}

void GameManager::winner(){
	//end of game, currentplayer lost
	//TODO display victory/lose screen
}

GameManager::GameManager(){
	player[0] = nullptr;
	player[1] = nullptr;
	turnCount = 0;
	currentPlayer = 0;
}

GameManager::~GameManager()
{
	delete player[0];
	delete player[1];
}
