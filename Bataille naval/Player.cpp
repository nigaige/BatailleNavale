#include "Utils.h"


bool Player::placeShip(int shipIndex, int x, int y, bool orientation){
		ships_[shipIndex]->orientation(orientation);
		ships_[shipIndex]->pos(x, y);
		//test return value, if false, ship couldn't be place and reask input
		return grille_->addShip(*ships_[shipIndex], x, y);
}

Player::Player(){
	grille_ = new Map();
	//TODO BETTER INIT?
	ships_[0] = new Ship(2);
	ships_[1] = new Ship(3);
	ships_[2] = new Ship(3);
	ships_[3] = new Ship(4);
	ships_[4] = new Ship(5);
	HP_ = 17;
}

Player::~Player(){

	for (int i = 0; i < sizeof(ships_) / sizeof(Ship); i++) {
		delete ships_[i];
	}
	delete grille_;
}
