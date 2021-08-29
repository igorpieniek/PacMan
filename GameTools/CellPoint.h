#pragma once

#include "MapCell.h"

enum class PointCat : int {
	ZER0  = 0,
	NORMAL = 1,
	SPECIAL = 10,
	GHOST_CATCH =200 
};

class CellPoint : public MapCell{
public:
	CellPoint(Position pos, PointCat points) : MapCell(pos, Category::FREE),
										  point(points) {};
	
	PointCat getPointClass() const;
	int getPoints() const;
	int takePoints();

private:
	PointCat  point;

};

