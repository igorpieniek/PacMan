#pragma once

#include "MoveAlgorithm.h"
#include "SafeMovement.h"
#include "MapManager.h"
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <map>

class RandMove: public MoveAlgorithm{
public:
	RandMove(CoordType step = { 1 }) : moveTool(step) {};

	void update(Position& current) override;
	void setStepResolution(CoordType res) override;
	void reset() override;

private:
	int getRandomValue(int min, int max);

	Direction getBestDirection(Position& center);
	std::vector<Direction> getAllPossibleDirecions(const Position& pos);

	void deleteCurrentDirection(std::vector<Direction>& dir);
	void moveProcess(Position& pos);

	Direction currentDirection{};
	SafeMovement moveTool;
	bool isInitialized = false;

	std::random_device rd;
	std::mt19937 generator{rd()};

	const std::vector<Direction> allDirections = {
		Direction::EAST, Direction::NORTH, 
		Direction::SOUTH, Direction::WEST
	};

};