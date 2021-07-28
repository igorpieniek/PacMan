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

	void getNextPosition(Position& current) override;
	void setStepResolution(CoordType res) override;
	void reset() override;

private:
	int getRandomValue(int min, int max);

	Direction getBestDirection(Position& center);

	void deleteCurrentDirection(std::vector<Direction>& dir);
	void moveProcess(Position& pos);


	Direction currentDirection;
	Movement moveTool;
	bool isInitialized = false;
};