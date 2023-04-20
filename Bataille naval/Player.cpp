#include "Utils.h"


void Player::placeShip(){
	for (int i = 0; i < sizeof(ships_); i++) {
		//TODO get input
		int inputX = i, inputY = i;
		bool orientation = false;
		ships_[i]->orientation(orientation);
		ships_[i]->pos(inputX, inputY);
		//TODO test return value, if false, ship couldn't be place and reask input
		grille_->addShip(*ships_[i], inputX, inputY);
	}
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

	for (int i = 0; i < sizeof(ships_); i++) {
		delete ships_[i];
	}
	delete grille_;
}
