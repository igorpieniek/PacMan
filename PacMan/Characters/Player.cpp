#include "Player.h"
#include <exception>

Player::Player(Position startPos, std::shared_ptr<MoveAlgorithm> moveAlg) :
	Character(startPos),
	prevPos(startPos),
	currentDir(Direction::EAST),
	moveManag(moveAlg)	
{
	if (MapManager::instance().isOccupied(startPos)) {
		throw std::runtime_error("Bad player position: selected position is occupied!");
	}
};

void Player::notify(Event evt){
	switch (evt)
	{
	case Event::PLAYER_CATCHED:
		--numberOfLifes;
		if (numberOfLifes == 0) {
			mediator->notify(Event::END_OF_LIVES);
			return;
		}
		std::cout << "Player : LIFE_LOST - remaining: " << numberOfLifes << std::endl;
		break;
	case Event::RESTART_POSITIONS:
		restoreInitialPosition();
		is_moving = false;
		currentDir = Direction::EAST;
		moveManag->reset();
		break;
	case Event::STOP_MOTION:
		stopMotion();
		break;
	case Event::ALLOW_MOTION:
		unblockMotion();
		break;
	case Event::RESET_GAME:
		numberOfLifes = 3;
		break;
	default:
		break;
	}
}

void Player::update(){
	if (isMotionBlocked) return;
	Position cpy = currentPostion;
	moveManag->update(currentPostion);
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



