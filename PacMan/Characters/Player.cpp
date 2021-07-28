#include "Player.h"




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

void Player::update(){
	Position cpy = currentPostion;
	moveManag->getNextPosition(currentPostion);
	updatePrevPosAndDir(cpy, currentPostion);
}

void Player::updatePrevPosAndDir(Position& suspectPos, Position& current){
	Direction newDir = getMoveDir(suspectPos, current);
	if (suspectPos != current) {
		prevPos = suspectPos;
		currentDir = newDir;
		is_moving = true;
	}
	else if (is_moving) {
		is_moving = false;
	}
}



