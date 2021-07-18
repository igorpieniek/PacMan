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
	if (isNextPositionFree(pos, dir)) {
		moveInDirDanger(pos, dir);
	}
}

bool SafeMovement::isNextPositionFree(Position& pos, Direction dir){
	Position temp = pos.getIntPos();
	tempDangerMoveTool.moveInDir(temp, dir);
	if (MapManager::instance().isOccupied(temp)) return false;
	else return true;
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
