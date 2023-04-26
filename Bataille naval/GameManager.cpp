#include "Utils.h"

void GameManager::init(){
	gameState = GAMEINIT;
	turnCount = 0;
	currentPlayer = 0;
	currentShip = 0;
	delete player[0];//In case the function is called again to prevent memory leak
	delete player[1];
	player[0] = new Player();
	player[1] = new Player();
	client = new Client();
	client->init("localhost");
	client->open();
}





void GameManager::game(GameInput& input){
	gameState = GAMERUNNING;
	switch (gameState){
	case GAMEINIT:
		initShip(input);
		break;

	case GAMERUNNING:
		turn(input);
		if (testVictory())
			gameState = GAMEFINISH;
		break;

	case GAMEFINISH:
		winner();
		break;

	default:
		break;
	}
}


void GameManager::initShip(GameInput& input){
	if(
		player[currentPlayer]->
		placeShip(currentShip,input.x(),input.y(), input.rightClick())
	){
		currentShip++;
		if (currentShip == 5){
			currentPlayer++;
			currentShip = 0;
		}
	}
	if (currentPlayer == 2) {
		gameState = GAMERUNNING;
	}
}

void GameManager::turn(GameInput& input){
	std::string temp = "S : " + std::to_string(input.x()) + ", " + std::to_string(input.y()) + "\n";
	const char* shootBuffer = temp.c_str();
	client->sendBuffer(shootBuffer);
	if (player[currentPlayer]->grille().shoot(input.x(), input.y())) {
		player[(currentPlayer == 1) ? 0 : 1]		//otherPlayer
			->HP(player[currentPlayer]->HP() - 1);	//reduce their hp
	};
	temp = "R : " + std::to_string(player[currentPlayer]->grille().shoot(input.x(), input.y())) + "\n";
	const char* resultBuffer = temp.c_str();
	client->sendBuffer(resultBuffer);
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

GameManager::~GameManager(){
	delete player[0];
	delete player[1];
}
