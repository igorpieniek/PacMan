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

void Movement::setStepSize(int siz){
	stepSize = siz;
}
