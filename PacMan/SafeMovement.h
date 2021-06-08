#pragma once

#ifndef __SAFEMOVEMENT_H__
#define __SAFEMOVEMENT_H__

#include "MapManager.h"
#include "Movement.h"


class SafeMovement : public Movement {
public:
	SafeMovement(int step = { 1 }) :
		Movement(step) {};

	void moveUp(Position& pos) override;
	void moveDown(Position& pos) override;
	void moveLeft(Position& pos) override;
	void moveRight(Position& pos) override;

	void moveInDir(Position& pos, Direction dir) override;

private:
	bool isNextPositionFree(Position pos, Direction dir);
};

#endif //__SAFEMOVEMENT_H__