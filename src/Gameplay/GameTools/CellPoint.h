#pragma once

#include "Position.h"

enum class PointCat : int {
	ZER0  = 0,
	NORMAL = 1,
	SPECIAL = 10,
	GHOST_CATCH =200 
};

class CellPoint : public Position{
public:
	CellPoint(Position pos, PointCat points) : Position(pos),
										  point(points) {};
	
	PointCat getPointClass() const;
	int getPoints() const;
	int takePoints();

private:
	PointCat point{};

};

