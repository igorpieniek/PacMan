#include "Player.h"

Player::Player(Position startPos, std::shared_ptr<MoveAlgorithm> moveAlg) :
	Character(startPos),
	prevPos(startPos),
	currentDir(Direction::EAST),
	moveManag(moveAlg)	{};

void Player::notify(Event evt){
	if (evt == Event::LIFE_LOST) {
		--numberOfLifes;		
		if (numberOfLifes == 0) {
			mediator->notify(Event::END_OF_LIVES);
			return;
		}
		std::cout << "Player : LIFE_LOST - remaining: " << numberOfLifes << std::endl;
	}
	if (evt == Event::RESTART_POSITIONS) {
		restoreInitialPosition();
		is_moving = false;
		currentDir = Direction::EAST;
		moveManag->reset();
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



