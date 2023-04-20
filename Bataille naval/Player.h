#pragma once
class Player{
private:

	Map* grille_;
	int HP_;
	Ship* ships_[5];

public:
	Player();
	virtual ~Player();
};

