#include "Utils.h"

bool Map::isCoordInGrid(int x, int y){
	return x >= 0 && x<SIZE_X && y>=0 && y<SIZE_Y;
}

bool Map::addShip(Ship& ship, int x, int y){
	//Test if ship fit
	//store it in map
	//store coordinate in ship
	return false;
}

bool Map::canShipFit(Ship& ship, int x, int y)
{
	//is coordinate in grid
	if (!isCoordInGrid(x, y)) throw "coord not in grid";
	//ship orientation
	//fit in grid with its size
	if(ship.orientation()?
		!isCoordInGrid(x,y+ ship.size()):
		!isCoordInGrid(x + ship.size(),y)
		)return false;
	
	//Check if place is empty
	for (int i = 0; i < ship.size(); i++) {
		if (ship.orientation() ?
			isShipHere(x, y + i) :
			isShipHere(x + i, y)
			)return false;
	}

	//PlaceBoat
	placeShip(ship, x, y);
	return false;
}

bool Map::isShipHere(int x, int y) {
	return grille[x][y] == 1;
}
void Map::placeShip(Ship& ship, int x, int y){
	for (int i = 0; i < ship.size(); i++) {
		if (ship.orientation()) {
			grille[x][y + i] = 1;
		}
		else {
			grille[x + i][y] = 1;
		}
	}
}
bool Map::shoot(int x, int y)
{
	if (!isCoordInGrid(x, y)) throw "coord not in grid";

	if (isShipHere(x, y)) {
		if (grille[x][y] == 1) {
			grille[x][y] = 2;
			return true;
		}
		return false;
	}
	grille[x][y] = 3;
	return false;
}
Map::Map(){
	for (int i = 0; i < 10; i++) {
		for (int j; j < 10; j++) {
			grille[i][j] = 0;
		}
	}
}
Map::~Map(){
}
