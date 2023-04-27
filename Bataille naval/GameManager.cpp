#include "Utils.h"

void GameManager::init(){
	gameState = GAMEINIT;
	turnCount = 0;
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
	case GAMEINIT://Place the ship
		initShip();
		break;
	case GAMEWAITSTART://waiting otherPlayer
		readWaitStart();
		break;
	case GAMEWAITTURN:
		waitPlayerNumber();
		break;
	case GAMERUNNINGISTURN:
		sendShot();
		if (testVictory())
			gameState = GAMEFINISH;
		break;
	case GAMESHOTSENT:
		waitShootResult();
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

void GameManager::readWaitStart(){
	std::string out = client->receiveBuffer();
	if (out.size() == 0) return;//nothing recieved
	if (out.find("P") == 0) {
		if (out.find("P") == 2) {
			gameState = GAMEWAITTURN;
		}
	}
}


void GameManager::initShip(){
	if (input->leftClick() && input->currentGrid() == 1) {
		input->leftClick(false);
		if (
			player[0]->
			placeShip(currentShip, input->x(), input->y(), input->rightClick())
			) {
			printf("boat placed");
			currentShip++;
			if (currentShip == 5) {
				gameState = GAMEWAITSTART;
				client->sendBuffer("R:1");
			}
		}
	}
}

void GameManager::sendShot(){
	if (input->leftClick() && input->currentGrid() == 2) {
		input->leftClick(false);
		player[0]->xShot(input->x());
		player[0]->yShot(input->y());
		std::string temp = "S : " + std::to_string(player[0]->xShot()) + ", " + std::to_string(player[0]->yShot()) + "\n";
		const char* shootBuffer = temp.c_str();
		client->sendBuffer(shootBuffer);
		gameState = GAMESHOTSENT;
	}
}


void GameManager::recieveShoot(){
	const char* resultBuffer;
	std::string out = client->receiveBuffer();
	if (out.size() == 0) return;//nothing recieved
	if (out.find("S") == 1) {
		int x = stoi(out.substr(0, out.find(",")));
		int y = stoi(out.substr(out.find(","),out.length()));
		if (player[0]->grille().shoot(x, y)) {
			player[(0 == 1) ? 0 : 1]		//otherPlayer
				->HP(player[0]->HP() - 1);	//reduce their hp
			resultBuffer = "R : 1";
			client->sendBuffer(resultBuffer);
		}
		else {
			resultBuffer = "R : 0";
			client->sendBuffer(resultBuffer);
		}
	}
}

void GameManager::waitShootResult()
{
	std::string out = client->receiveBuffer();
	if (out.size() == 0) return;//nothing recieved
	if (out.find("R") == 1) {
		std::string result = out.substr(4, out.length());
		player[1]->grille().wasShot(player[0]->xShot(), player[0]->yShot(), result == "1" ? true : false);
		
	}
}

void GameManager::waitPlayerNumber()
{
	std::string out = client->receiveBuffer();
	if (out.size() == 0) return;//nothing recieved
	if (out.find("T") == 1) {
		std::string result = out.substr(2, out.length());
		gameState = result == "1" ? GAMERUNNINGISTURN : GAMERUNNINGNOTTURN;
	}
}

void GameManager::turn(){
	/*
	std::string temp = "S : " + std::to_string(input.x()) + ", " + std::to_string(input.y()) + "\n";
	const char* shootBuffer = temp.c_str();
	client->sendBuffer(shootBuffer);
	if (player[0]->grille().shoot(input.x(), input.y())) {
		player[(0 == 1) ? 0 : 1]		//otherPlayer
			->HP(player[0]->HP() - 1);	//reduce their hp
	};
	temp = "R : " + std::to_string(player[0]->grille().shoot(input.x(), input.y())) + "\n";
	const char* resultBuffer = temp.c_str();
	client->sendBuffer(resultBuffer);
	turnCount++;
	0 = (0 == 1) ? 0 : 1;	//Swap player*/
}


bool GameManager::testVictory(){
	return player[0]->HP() > 0;
}

void GameManager::winner(){
	//end of game, 0 lost
	//TODO display victory/lose screen
}





void GameManager::drawGame(sf::RenderWindow& window){


	window.clear();
	player[0]->grille().drawGrid(window, PLAYER_1_GRID_POSX, PLAYER_1_GRID_POSY);
	player[1]->grille().drawGrid(window, PLAYER_2_GRID_POSX, PLAYER_2_GRID_POSY);

	if (gameState == GAMEINIT) {
		drawShipPreview(window);
	}

	drawUI(window);

	window.display();

}

void GameManager::drawShipPreview(sf::RenderWindow& window)
{
	if (input->currentGrid() != 1) return;
	if (player[0]->grille().canShipFit(player[0]->ship(currentShip), input->x(), input->y(), input->rightClick()))
	{
		sf::CircleShape shape(SLOT_SIZE_X / 2);
		if (input->rightClick())
		{
			for (int i = 0; i < player[0]->ship(currentShip).size(); i++) {
				shape.setPosition(sf::Vector2f(PLAYER_1_GRID_POSX + input->x() * SLOT_SIZE_X, PLAYER_1_GRID_POSY + (i + input->y()) * SLOT_SIZE_Y));
				shape.setFillColor(sf::Color(0, 255, 0));
				window.draw(shape);
			}
		}
		else
		{
			for (int i = 0; i < player[0]->ship(currentShip).size(); i++) {
				shape.setPosition(sf::Vector2f(PLAYER_1_GRID_POSX + (i + input->x()) * SLOT_SIZE_X, PLAYER_1_GRID_POSY +  input->y() * SLOT_SIZE_Y));
				shape.setFillColor(sf::Color(0, 255, 0));
				window.draw(shape);
			}
		}
	}
}

void GameManager::drawUI(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("../Ressources/Font/Arial.ttf")) return;

	std::string string;
	if (gameState == 0)
		string = "Please place your boats.";
	else if (gameState == 1)
		string = "Waiting for the other player.";
	else if (gameState == 2)
		string = "It's your turn, please select a cell to shoot.";
	else if (gameState == 3)
		string = "It's the opponent turn, please wait for his shot.";
	else if (gameState == 4)
		string = "PLAYER win !";

	sf::Text text(string, font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 25));
	text.setPosition(sf::Vector2f(window.getSize().x / 2, 25));
	window.draw(text);
}

GameManager::GameManager(){
	player[0] = nullptr;
	player[1] = nullptr;
	turnCount = 0;
}

GameManager::~GameManager(){
	delete player[0];
	delete player[1];
}
