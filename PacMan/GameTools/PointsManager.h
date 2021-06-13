#pragma once

#ifndef __POINTSMANAGER_H__
#define __POINTSMANAGER_H__

#include "MapManager.h"
#include "CellPoint.h"
#include <vector>

class PointsManager{
public:
	PointsManager(int specialAmount) : specialPointsAmount(specialAmount) 
	{
		createCellPointArray();
	};
	
private:
	int currentPoints;
	int specialPointsAmount;
	std::vector<CellPoint> cellPoints;


	void createCellPointArray();


};

#endif // __POINTSMANAGER_H__

