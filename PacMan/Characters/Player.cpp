#include "Player.h"

void Player::draw(){
	std::cout << " " + symbol;
}

void Player::moveUp(){
	moveTool.moveUp(currentPostion);
}

void Player::moveDown(){
	moveTool.moveDown(currentPostion);
}

void Player::moveLeft(){
	moveTool.moveLeft(currentPostion);
}

void Player::moveRight(){
	moveTool.moveRight(currentPostion);
}

void Player::addPoints(int p){
	numberOfPoints += p;
}

void Player::notify(Event evt){
	if (evt == Event::LIFE_LOST) {
		--numberOfLifes;
		if (numberOfLifes == 0) {
			mediator->notify(Event::END_OF_LIVES);
		}
	}
}



