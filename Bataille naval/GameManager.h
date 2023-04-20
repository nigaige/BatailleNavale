#pragma once
class GameManager
{
	Player* player[2];
	int turnCount;
	int currentPlayer;


public:
	void init();
	void game();
	void turn();
	bool testVictory();
	void winner();

	GameManager();
	virtual ~GameManager();
};

