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
		printf("GAMEINIT\n");
		initShip();
		break;
	case GAMEWAITSTART://waiting otherPlayer
		printf("GAMEWAITSTART\n");

		std::cout << "ça bloque ?" << std::endl;
		readWaitStart();
		//std::cout << "a bah non sa bloque pas" << std::endl;
		break;
	case GAMEWAITTURN:
		printf("GAMEWAITTURN\n");

		waitPlayerNumber();
		break;
	case GAMERUNNINGISTURN:
		printf("GAMERUNNINGISTURN\n");

		sendShot();
		break;
	case GAMESHOTSENT:
		printf("GAMESHOTSENT\n");

		waitShootResult();
		break;
	case GAMERUNNINGNOTTURN:
		printf("GAMERUNNINGNOTTURN\n");

		recieveShoot();
		break;
	case GAMEFINISHLOSE:
		printf("GAMEFINISHLOSE\n");

		winner();
		break;
	case GAMEFINISHWIN:
		printf("GAMEFINISHWIN\n");
		break;
	default:
		break;
	}

	

}

void GameManager::readWaitStart(){
	std::string out = client->receiveBuffer();
	if (out.size() == 0) return;//nothing recieved
	if (out.find("P") == 0) {
		std::cout << "hey" << std::endl;
		if (out.find("2") == 2) {
			std::cout << "2" << std::endl;
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
			printf("boat placed\n");
			currentShip++;
			if (currentShip == 5) {
				gameState = GAMEWAITSTART;
				client->sendBuffer("R:1");
			}
		}
	}
	input->leftClick(false);
}

void GameManager::sendShot(){
	if (input->leftClick() && input->currentGrid() == 2) {
		input->leftClick(false);
		player[0]->xShot(input->x());
		player[0]->yShot(input->y());
		std::string temp = "S:" + std::to_string(player[0]->xShot()) + "," + std::to_string(player[0]->yShot()) + "\n";
		const char* shootBuffer = temp.c_str();
		client->sendBuffer(shootBuffer);
		gameState = GAMESHOTSENT;
	}
	input->leftClick(false);
}


void GameManager::recieveShoot(){
	const char* resultBuffer;
	std::string out = client->receiveBuffer();
	if (out.size() == 0) return;//nothing recieved
	if (out.find("S") == 0) {
		int x = stoi(out.substr(2,3));
		int y = stoi(out.substr(4,out.length()));
		if (player[0]->grille().shoot(x, y)) {
			player[0]->HP(player[0]->HP() - 1);	//reduce their hp
			resultBuffer = "R:1";
			client->sendBuffer(resultBuffer);
		}
		else {
			resultBuffer = "R:0";
			client->sendBuffer(resultBuffer);
		}

		if (testVictory()) {
			resultBuffer = "F:0";
			client->sendBuffer(resultBuffer);
			gameState = GAMEFINISHLOSE;
			return;
		}
			
		gameState = GAMERUNNINGISTURN;

	}

	if (out.find("F") == 0) {
		gameState = GAMEFINISHWIN;

	}

}

void GameManager::waitShootResult()
{
	std::string out = client->receiveBuffer();
	if (out.size() == 0) return;//nothing recieved
	if (out.find("R") == 0) {
		std::string result = out.substr(2, out.length());
		player[1]->grille().wasShot(player[0]->xShot(), player[0]->yShot(), result == "1" ? true : false);
		gameState = GAMERUNNINGNOTTURN;
	}
}

void GameManager::waitPlayerNumber()
{
	std::string out = client->receiveBuffer();
	std::cout <<"player number" << out;
	if (out.size() == 0) return;//nothing recieved
	
	if (out.find("T") == 0) {
		
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
	return player[0]->HP() == 0;
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
	if (gameState == GAMERUNNINGISTURN) {
		drawShootPreview(window);
	}

	drawUI(window);

	window.display();

}

void GameManager::drawShootPreview(sf::RenderWindow& window)
{
	if (input->currentGrid() != 2) return;
	sf::CircleShape shape(SLOT_SIZE_X / 2);
	shape.setPosition(sf::Vector2f(PLAYER_2_GRID_POSX + input->x() * SLOT_SIZE_X, PLAYER_2_GRID_POSY + (input->y()) * SLOT_SIZE_Y));
	shape.setFillColor(sf::Color(255, 0, 0));
	window.draw(shape);

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

/*
#define GAMEINIT 0
#define GAMEWAITSTART 1
#define GAMEWAITTURN 2
#define GAMERUNNINGISTURN 3
#define GAMESHOTSENT 4
#define GAMERUNNINGNOTTURN 5
#define GAMEFINISH 6

*/

void GameManager::drawUI(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("../Ressources/Font/Arial.ttf")) return;

	std::string string;
	if (gameState == GAMEINIT)
		string = "Please place your boats.";
	else if (gameState == GAMEWAITSTART)
		string = "Waiting for the other player.";
	else if (gameState == GAMERUNNINGISTURN)
		string = "It's your turn, please select a cell to shoot.";
	else if (gameState == GAMERUNNINGNOTTURN)
		string = "It's the opponent turn, please wait for his shot.";
	else if (gameState == GAMEFINISHLOSE)
		string = "YOU LOSE!!!!";
	else if (gameState == GAMEFINISHWIN)
		string = "YOU WIN!!!!";

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
