#pragma once


#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__

#include "Position.h"

class Movement{
public:

	Movement(int step = {1}) : stepSize(step) {};
	void moveUp(Position& pos);
	void moveDown(Position& pos);
	void moveLeft(Position& pos);
	void moveRight(Position& pos);

	void setStepSize(int siz);

private:
	int stepSize;

};

#endif //__MOVEMENT_H__