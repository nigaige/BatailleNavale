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

	input = new GameInput();
}





void GameManager::readInput(sf::RenderWindow *window){

	input->mousePos(window);
	input->checkCurrentGrid();
	input->windowInput();
	

	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
		else if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				input->leftClick(true);
			}
			else if (event.mouseButton.button == sf::Mouse::Right) {
				input->swapClick();
			}
		}
	}
}

void GameManager::game(){
	switch (gameState){
	case GAMEINIT:
		initShip();
		break;
	case GAMEWAITSTART:
		readWaitStart();
		break;
	case GAMERUNNINGISTURN:
		sendShot();
		if (testVictory())
			gameState = GAMEFINISH;
		break;
	case GAMERUNNINGNOTTURN:
		recieveShoot();
		break;

	case GAMEFINISH:
		winner();
		break;

	default:
		break;
	}

	

}

void GameManager::readWaitStart()
{
}


void GameManager::initShip(){
	if (input->leftClick() && input->currentGrid() == 1) {
		input->leftClick(false);
		if (
			player[currentPlayer]->
			placeShip(currentShip, input->x(), input->y(), input->rightClick())
			) {
			printf("boat placed");
			currentShip++;
			if (currentShip == 5) {
				gameState = GAMEWAITSTART;
			}
		}
	}
}

void GameManager::readSocketQueu()
{
}

void GameManager::sendShot()
{
}

void GameManager::recieveShoot()
{
}

void GameManager::turn(){
	/*
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
	currentPlayer = (currentPlayer == 1) ? 0 : 1;	//Swap player*/
}


bool GameManager::testVictory(){
	return player[currentPlayer]->HP() > 0;
}

void GameManager::winner(){
	//end of game, currentplayer lost
	//TODO display victory/lose screen
}





void GameManager::drawGame(sf::RenderWindow& window){


	window.clear();
	player[0]->grille().drawGrid(window, PLAYER_1_GRID_POSX, PLAYER_1_GRID_POSY);
	player[1]->grille().drawGrid(window, PLAYER_2_GRID_POSX, PLAYER_2_GRID_POSY);

	if (gameState == GAMEINIT) {
		drawShipPreview(window);
	}

	window.display();

}

void GameManager::drawShipPreview(sf::RenderWindow& window)
{
	if (input->currentGrid() != 1) return;
	if (player[currentPlayer]->grille().canShipFit(player[currentPlayer]->ship(currentShip), input->x(), input->y(), input->rightClick()))
	{
		sf::CircleShape shape(SLOT_SIZE_X / 2);
		if (input->rightClick())
		{
			for (int i = 0; i < player[currentPlayer]->ship(currentShip).size(); i++) {
				shape.setPosition(sf::Vector2f(PLAYER_1_GRID_POSX + input->x() * SLOT_SIZE_X, PLAYER_1_GRID_POSY + (i + input->y()) * SLOT_SIZE_Y));
				shape.setFillColor(sf::Color(0, 255, 0));
				window.draw(shape);
			}
		}
		else
		{
			for (int i = 0; i < player[currentPlayer]->ship(currentShip).size(); i++) {
				shape.setPosition(sf::Vector2f(PLAYER_1_GRID_POSX + (i + input->x()) * SLOT_SIZE_X, PLAYER_1_GRID_POSY +  input->y() * SLOT_SIZE_Y));
				shape.setFillColor(sf::Color(0, 255, 0));
				window.draw(shape);
			}
		}
	}
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
