#pragma once

#include "Position.h"
#include "MapCell.h"
#include "SafeMovement.h"


class MoveAlgorithm{
public:
	virtual void update(Position& current) = 0;
	virtual void setStepResolution(CoordType res) = 0;
	virtual void reset() = 0;
	virtual ~MoveAlgorithm() {};

protected:
	SafeMovement moveTool{};
	MoveAlgorithm(){};
};
