#include "Utils.h"

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

	for (int i = 0; i < sizeof(ships_); i++) {
		delete ships_[i];
	}
	delete grille_;
}
