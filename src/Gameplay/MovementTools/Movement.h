#pragma once

#include "Position.h"

enum class Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

Direction getOpprositeDirection(const Direction& dir);
Direction getNextDirection(const Direction& dir);
Direction getMoveDir(const Position& prev, const Position& future);
void printDirection(const Direction& dir);

class Movement{
public:
	Movement(CoordType step = { 1 });
	virtual void moveUp(Position& pos);
	virtual void moveDown(Position& pos);
	virtual void moveLeft(Position& pos);
	virtual void moveRight(Position& pos);

	virtual void moveInDir(Position& pos, Direction dir);

	void setStepSize(CoordType siz);

protected:
	CoordType stepSize{};

private:
	void checkStepSizeIsPositive();

};