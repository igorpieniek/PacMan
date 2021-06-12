#pragma once

#ifndef __POINTSMANAGER_H__
#define __POINTSMANAGER_H__

#include "MapManager.h"
#include "CellPoint.h"
#include <vector>
#include <cstdlib>

class PointsManager{
public:
	PointsManager(int specialAmount) : specialPointsAmount(specialAmount) {};
	
private:
	int currentPoints;
	int specialPointsAmount;
	std::vector<CellPoint> cellPoints;


	void createCellPointArray();


};

#endif // __POINTSMANAGER_H__

