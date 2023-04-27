#pragma once

#define GAMEINIT 0
#define GAMEWAITSTART 1
#define GAMEWAITTURN 2
#define GAMERUNNINGISTURN 3
#define GAMERUNNINGNOTTURN 4
#define GAMEFINISH 5

class GameManager
{
	Player* player[2];
	Client* client;
	int turnCount;
	int currentPlayer;
	int currentShip;
	int gameState;
	GameInput* input;
	sf::Event event;

public:
	void init();
	void turn();
	bool testVictory();
	void winner();


	//gameLoop
	void readInput(sf::RenderWindow* window);
	void game();
	void readWaitStart();
	void initShip();
	void readSocketQueu();
	void sendShot();
	void recieveShoot();




	void drawGame(sf::RenderWindow& window);
	void drawShipPreview();

	GameManager();
	virtual ~GameManager();
};

