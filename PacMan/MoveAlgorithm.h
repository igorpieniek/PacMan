#pragma once

#ifndef __MOVEALGORITHM_H__
#define __MOVEALGORITHM_H__

#include "Position.h"
#include "MapCell.h"
#include "MapManager.h"



class MoveAlgorithm{
public:
	virtual Position getNextPosition(Position& current) = 0;
	virtual void setStepResolution(int res) = 0;
	virtual ~MoveAlgorithm() {};
protected:

	MoveAlgorithm(MapManager* manag) : mapManager(manag) {};
	MapManager* mapManager;
	
};


#endif //__MOVEALGORITHM_H__
