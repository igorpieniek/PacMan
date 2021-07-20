#pragma once

#include "MoveAlgorithm.h"
#include "Movement.h"
#include "MapManager.h"
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

class RandMove: public MoveAlgorithm{
public:
	RandMove(CoordType step = 1) : moveTool(step) {
		currentDirection = Direction::NORTH;
	};

	Position getNextPosition(Position& current) override;
	void setStepResolution(CoordType res) override;

private:
	int getRandomValue(int min, int max);

	Direction getBestDirection(Position& center);

	void deleteCurrentDirection(std::vector<Direction>& dir);
	Position moveProcess(Position& pos);


	Direction currentDirection;
	Movement moveTool;
	bool isInitialized = false;
};