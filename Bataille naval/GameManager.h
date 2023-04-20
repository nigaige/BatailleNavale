#pragma once
class GameManager
{
	Player* player[2];
	int turnCount;
	int currentPlayer;


public:
	void init();
	void turn(int player);



	GameManager();
	virtual ~GameManager();
};

