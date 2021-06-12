#pragma once

#ifndef __CELLPOINT_H__
#define __CELLPOINT_H__

#include "MapCell.h"

enum class PointCat : int {
	ZER0  = 0,
	NORMAL = 1,
	SPECIAL = 10,
};

class CellPoint : public MapCell{
public:
	CellPoint(Position pos, PointCat points) : MapCell(pos, Category::FREE),
										  point(points) {};
	
	int getPoints();

private:
	PointCat  point;

};

#endif //__CELLPOINT_H__

