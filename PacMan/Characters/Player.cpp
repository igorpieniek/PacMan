#include "Player.h"


void Player::moveUp(){
	Position cpy = currentPostion;
	moveTool.moveUp(currentPostion);
	updatePrevPosAndDir(cpy, currentPostion, Direction::NORTH);
}

void Player::moveDown(){
	Position cpy = currentPostion;
	moveTool.moveDown(currentPostion);
	updatePrevPosAndDir(cpy, currentPostion, Direction::SOUTH);
}

void Player::moveLeft(){
	Position cpy = currentPostion;
	moveTool.moveLeft(currentPostion);
	updatePrevPosAndDir(cpy, currentPostion, Direction::WEST);
}

void Player::moveRight(){
	Position cpy = currentPostion;
	moveTool.moveRight(currentPostion);
	updatePrevPosAndDir(cpy, currentPostion, Direction::EAST);
}

void Player::notify(Event evt){
	if (evt == Event::LIFE_LOST) {
		--numberOfLifes;		
		if (numberOfLifes == 0) {
			mediator->notify(Event::END_OF_LIVES);
		}
		std::cout << "Player : LIFE_LOST - remaining: " << numberOfLifes << std::endl;
	}
	if (evt == Event::RESTART_POSITIONS) {
		restoreInitialPosition();
	}
}

void Player::updatePrevPosAndDir(Position& suspectPos, Position& current, Direction dir){
	if (suspectPos != current) {
		prevPos = suspectPos;
		currentDir = dir;
		is_moving = true;
	}
	else if (is_moving) {
		is_moving = false;
	}
}



