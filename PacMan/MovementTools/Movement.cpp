#include "Movement.h"

Direction getOpprositeDirection(const Direction& dir) {
	switch (dir) {
	case Direction::NORTH:
		return Direction::SOUTH;
	case Direction::SOUTH:
		return Direction::NORTH;
	case Direction::WEST:
		return Direction::EAST;
	case Direction::EAST:
		return Direction::WEST;
	default:
		return Direction();
		break;
	}
}

Direction getNextDirection(const Direction& dir) {
	int index = static_cast<int>(dir);
	if (index == 3) {
		return static_cast<Direction>(0);
	}

	return static_cast<Direction>(index+1);
}

Direction getMoveDir(const Position& prev, const Position& future){
	CoordType xdiff = future.getX() - prev.getX();
	CoordType ydiff = future.getY() - prev.getY();
	if		(xdiff == 0 && ydiff > 0) return Direction::NORTH;
	else if (xdiff == 0 && ydiff < 0) return Direction::SOUTH;
	else if (xdiff > 0 && ydiff == 0) return Direction::EAST;
	else if (xdiff < 0 && ydiff == 0) return Direction::WEST;
}

void printDirection(const Direction& dir){
	switch (dir) {
	case Direction::NORTH:
		std::cout << "NORTH";
		break;
	case Direction::SOUTH:
		std::cout << "SOUTH";
		break;
	case Direction::WEST:
		std::cout << "WEST";
		break;
	case Direction::EAST:
		std::cout << "EAST";
		break;
	default:
		std::cout << "Direction printing fail";
		break;
	}
}



Movement::Movement(CoordType step) : stepSize(step) 
{
	checkStepSizeIsPositive();
}

void Movement::moveUp(Position& pos){
	pos += Position{ 0, stepSize };
}

void Movement::moveDown(Position& pos){
	pos += Position{ 0, -stepSize };
}

void Movement::moveLeft(Position& pos){
	pos += Position{ -stepSize, 0};
}

void Movement::moveRight(Position& pos){
	pos += Position{ stepSize, 0 };
}

void Movement::moveInDir(Position& pos, Direction dir){
	switch (dir) {
	case Direction::NORTH:
		moveUp(pos);
		break;
	case Direction::EAST:
		moveRight(pos);
		break;
	case Direction::WEST:
		moveLeft(pos);
		break;
	case Direction::SOUTH:
		moveDown(pos);
		break;
	}
}

void Movement::setStepSize(CoordType siz){
	stepSize = siz;
	checkStepSizeIsPositive();
}

void Movement::checkStepSizeIsPositive(){
	if (stepSize < 0) {
		throw std::runtime_error("Movement: step size can't be negative! ");
	}
}

