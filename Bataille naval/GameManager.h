#pragma once

#define GAMEINIT 0
#define GAMEWAITSTART 1
#define GAMEWAITTURN 2
#define GAMERUNNINGISTURN 3
#define GAMESHOTSENT 4
#define GAMERUNNINGNOTTURN 5
#define GAMEFINISHLOSE 6
#define GAMEFINISHWIN 7

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
	void sendShot();
	void recieveShoot();
	void waitShootResult();
	void waitPlayerNumber();


	void drawGame(sf::RenderWindow& window);
	void drawShipPreview(sf::RenderWindow& window);
	void drawShootPreview(sf::RenderWindow& window);
	void drawUI(sf::RenderWindow& window);

	GameManager();
	virtual ~GameManager();
};

