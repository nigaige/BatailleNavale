#pragma once

#define GAMEINIT 0
#define GAMERUNNING 1
#define GAMEFINISH 2

class GameManager
{
	Player* player[2];
	Client* client;
	int turnCount;
	int currentPlayer;
	int currentShip;
	int gameState;

public:
	void init();
	void game(GameInput& input);
	void initShip(GameInput& input);
	void turn(GameInput& input);
	bool testVictory();
	void winner();

	GameManager();
	virtual ~GameManager();
};

