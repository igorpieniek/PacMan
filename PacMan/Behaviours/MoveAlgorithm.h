#pragma once

#include "Position.h"
#include "MapCell.h"


class MoveAlgorithm{
public:
	virtual void getNextPosition(Position& current) = 0;
	virtual void setStepResolution(CoordType res) = 0;
	virtual void reset() = 0;
	virtual ~MoveAlgorithm() {};

protected:
	MoveAlgorithm(){};
};
