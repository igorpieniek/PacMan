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

	Direction getBestDirection(Position& center);

	void deleteCurrentDirection(std::vector<Direction>& dir);
	Position moveProcess(Position& pos);


	Direction currentDirection;
	Movement moveTool;
	bool isInitialized = false;



};

#endif // __RANDMOVE_H__