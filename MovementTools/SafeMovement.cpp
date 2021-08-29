#include "SafeMovement.h"

void SafeMovement::moveUp(Position& pos){
	moveInDir(pos, Direction::NORTH);
}

void SafeMovement::moveDown(Position& pos){
	moveInDir(pos, Direction::SOUTH);
}

void SafeMovement::moveLeft(Position& pos){
	moveInDir(pos, Direction::WEST);
}

void SafeMovement::moveRight(Position& pos){
	moveInDir(pos, Direction::EAST);
}

void SafeMovement::moveInDir(Position& pos, Direction dir){
	if (isNextPositionFree(pos, dir) && isMoveInDirAllowed(pos,dir)) {
		moveInDirDanger(pos, dir);
	}
}

bool SafeMovement::isNextPositionFree(Position& pos, Direction dir){
	Position temp = pos;
	tempDangerMoveTool.moveInDir(temp, dir);
	if ( !MapManager::instance().isOccupied(temp)) return true;

	temp = temp.getIntPos();
	if (pos.distance(temp) >= (1.0f + (0.5*stepSize))) return true;
	else return false;

}

bool SafeMovement::isMoveInDirAllowed(Position& pos, Direction dir){
	if (dir == Direction::NORTH || dir == Direction::SOUTH) {
		if (pos.isXCoordInt()) return true;
	}
	else if (dir == Direction::EAST || dir == Direction::WEST) {
		if (pos.isYCoordInt()) return true;
	}
	return false;
}

void SafeMovement::moveInDirDanger(Position& pos, Direction dir){
	switch (dir)
	{
	case Direction::NORTH:
		Movement::moveUp(pos);
		break;
	case Direction::EAST:
		Movement::moveRight(pos);
		break;
	case Direction::SOUTH:
		Movement::moveDown(pos);
		break;
	case Direction::WEST:
		Movement::moveLeft(pos);
		break;
	default:
		break;
	}

}
