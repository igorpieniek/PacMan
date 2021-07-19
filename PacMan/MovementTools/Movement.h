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

	Movement(CoordType step = {1}) : stepSize(step) {};
	virtual void moveUp(Position& pos);
	virtual void moveDown(Position& pos);
	virtual void moveLeft(Position& pos);
	virtual void moveRight(Position& pos);

	virtual void moveInDir(Position& pos, Direction dir);

	void setStepSize(CoordType siz);

protected:
	CoordType stepSize;

};





#endif //__MOVEMENT_H__