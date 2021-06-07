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

void Movement::setStepSize(int siz){
	stepSize = siz;
}

