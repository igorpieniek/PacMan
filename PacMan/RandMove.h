#pragma once

#ifndef __RANDMOVE_H__
#define __RANDMOVE_H__

#include "MoveAlgorithm.h"
#include "Movement.h"
#include "MapManager.h"
#include <cstdlib>
#include <vector>
#include <algorithm>

class RandMove: public MoveAlgorithm{
public:
	RandMove(int step = 1) : moveTool(step) {
		currentDirection = Direction::NORTH;
	};

	Position getNextPosition(Position& current) override;
	void setStepResolution(int res) override;

private:
	int getRandomValue(int min, int max);

	Direction getBestDirection(Position& center);

	void deleteCurrentDirection(std::vector<Direction>& dir);
	Position moveProcess(Position& pos);


	Direction currentDirection;
	Movement moveTool;
	bool isInitialized = false;
};

#endif // __RANDMOVE_H__