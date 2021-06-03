#pragma once


#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__

#include "Position.h"

enum class Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

Direction getOpprositeDirection(const Direction& dir);
void printDirection(const Direction& dir);

class Movement{
public:

	Movement(int step = {1}) : stepSize(step) {};
	void moveUp(Position& pos);
	void moveDown(Position& pos);
	void moveLeft(Position& pos);
	void moveRight(Position& pos);

	void moveInDir(Position& pos, Direction dir);

	void setStepSize(int siz);

private:
	int stepSize;

};

#endif //__MOVEMENT_H__