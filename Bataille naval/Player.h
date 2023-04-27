#pragma once
class Player{
private:

	Map* grille_;
	int HP_;
	Ship* ships_[5];
	int xShot_;
	int yShot_;

public:
	void HP(int HP) { HP_ = HP; }
	int HP() { return HP_; }
	void xShot(int x) { xShot_ = x; };
	int xShot() { return xShot_; };
	void yShot(int y) { yShot_ = y; };
	int yShot() { return yShot_; };
	Map& grille() { return *grille_; }
	Ship& ship(int index) { return *ships_[index]; };

	bool placeShip(int shipIndex, int x, int y, bool orientation);
	Player();
	virtual ~Player();
};

