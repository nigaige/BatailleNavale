#pragma once


class Map{

private:
	int grille[GRID_SIZE_X][GRID_SIZE_Y] = {};	//EMPTY 0 / SHIP 1 / HIT 2 / 3 MISS
public:

	//TODO grille getter
	//TODO grille slot getter

	bool isCoordInGrid(int x, int y);
	//Ship management
	bool addShip(Ship& ship, int x,int y);
	bool canShipFit(Ship& ship, int x, int y);
	bool isShipHere(int x, int y);
	void placeShip(Ship& ship, int x, int y);
	//Shoot
	bool shoot(int x, int y);


	Map();
	virtual ~Map();
};

