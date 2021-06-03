#pragma once

#ifndef __RANDMOVE_H__
#define __RANDMOVE_H__

#include "MoveAlgorithm.h"
#include "Movement.h"
#include <cstdlib>
#include <vector>
#include <algorithm>

class RandMove: public MoveAlgorithm{
public:
	RandMove(MapManager* manag, int step=1) :MoveAlgorithm(manag), moveTool(step) {
		currentDirection = Direction::NORTH;
	};

	Position getNextPosition(Position& current) override;



private:
	int getRandomValue(int min, int max);

	Position getPositionInDirection(Position& center, Direction dir);
	Direction getBestDirection(Position& center);

	Position firstMoveProcess(Position& pos);
	Position normalMoveProcess(Position& pos);

	Direction currentDirection;
	Movement moveTool;
	bool isInitialized = false;



};

#endif // __RANDMOVE_H__