#pragma once

#ifndef __POINTSMANAGER_H__
#define __POINTSMANAGER_H__

#include "MapManager.h"
#include "CellPoint.h"
#include <vector>

class PointsManager{
public:
	PointsManager(int specialAmount) : 
		specialPointsAmount{ specialAmount },
		currentPoints{ 0 }
	{
		createCellPointArray();
	};

	int getPoints()const { return currentPoints; };
	
private:
	int currentPoints;
	int specialPointsAmount;
	std::vector<CellPoint> cellPoints;


	void createCellPointArray();
	void addPoints(Position& pos);

};

#endif // __POINTSMANAGER_H__

