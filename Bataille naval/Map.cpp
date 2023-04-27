#include "Utils.h"

void Map::drawGrid(sf::RenderWindow& window, int offX, int offY)
{
	sf::CircleShape shape(SLOT_SIZE_X/2);
	for (int i = 0; i < GRID_SIZE_X; i++) {
		for (int j = 0; j < GRID_SIZE_Y; j++) {
			window.draw(drawSquare(SLOT_SIZE_X * i + offX, SLOT_SIZE_Y * j + offY));
			shape.setPosition(sf::Vector2f(SLOT_SIZE_X * i + offX, SLOT_SIZE_Y * j + offY));
			if (grille[i][j] == 0) continue;
			shape.setPosition(sf::Vector2f(SLOT_SIZE_X * i + offX, SLOT_SIZE_Y * j + offY));

			switch (grille[i][j]){
				case 0://EMPTY
					break;
				case 1://SHIP
					shape.setFillColor(sf::Color(128, 128, 128));
					break;
				case 2://HIT
					shape.setFillColor(sf::Color(255, 0, 0));
					break;
				case 3://MISS
					shape.setFillColor(sf::Color(255, 255, 255));
					break;
				default:
					break;
			}
			window.draw(shape);
		}
	}
}



sf::VertexArray Map::drawSquare(int offX, int offY){
	sf::VertexArray square(sf::LinesStrip, 5);
	int x0 = 0 + offX;
	int x1 = SLOT_SIZE_X + offX;
	int y0 = 0 + offY;
	int y1 = SLOT_SIZE_Y + offY;

	square[0].position = sf::Vector2f( x0 ,y0 );
	square[1].position = sf::Vector2f(x0, y1);
	square[2].position = sf::Vector2f(x1, y1);
	square[3].position = sf::Vector2f(x1, y0);
	square[4].position = sf::Vector2f(x0, y0);
	return square;

}

bool Map::isCoordInGrid(int x, int y){
	return x >= 0 && x<=GRID_SIZE_X && y>=0 && y<=GRID_SIZE_Y;
}

bool Map::addShip(Ship& ship, int x, int y){
	//Test if ship fit
	if (canShipFit(ship, x, y, ship.orientation())) {
		//store it in map
		placeShip(ship, x, y);
		return true;
	}
	return false;
}

bool Map::canShipFit(Ship& ship, int x, int y, bool orientation)
{
	//is coordinate in grid
	if (!isCoordInGrid(x, y)) throw "coord not in grid";
	//ship orientation
	//fit in grid with its size
	if (orientation ?
		!isCoordInGrid(x, y + ship.size()) :
		!isCoordInGrid(x + ship.size(), y)
		) return false;
	
	//Check if place is empty
	for (int i = 0; i < ship.size(); i++) {
		if (orientation ?
			isShipHere(x, y + i) :
			isShipHere(x + i, y)
			) return false;
	}
	return true;
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
		for (int j=0; j < 10; j++) {
			grille[i][j] = 0;
		}
	}
}
Map::~Map(){
}
