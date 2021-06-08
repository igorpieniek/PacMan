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
		Movement::moveInDir(pos, dir);
	}
}

bool SafeMovement::isNextPositionFree(Position pos, Direction dir){
	Movement::moveInDir(pos, dir);
	if (MapManager::instance().isOccupied(pos)) return false;
	else return true;
}
