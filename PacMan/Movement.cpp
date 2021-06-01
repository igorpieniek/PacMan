#include "Movement.h"

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
