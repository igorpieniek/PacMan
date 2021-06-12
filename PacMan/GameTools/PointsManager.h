#pragma once

#ifndef __POINTSMANAGER_H__
#define __POINTSMANAGER_H__

#include "MapManager.h"

class PointsManager{
public:
	PointsManager();
	
private:
	int maxAmountFreePositions;
	int currentPoints;
};

#endif // __POINTSMANAGER_H__

