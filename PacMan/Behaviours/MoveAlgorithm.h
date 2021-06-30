#pragma once

#ifndef __MOVEALGORITHM_H__
#define __MOVEALGORITHM_H__

#include "Position.h"
#include "MapCell.h"



class MoveAlgorithm{
public:
	virtual Position getNextPosition(Position& current) = 0;
	virtual void setStepResolution(CoordType res) = 0;
	virtual ~MoveAlgorithm() {};
protected:

	MoveAlgorithm(){};

	
};


#endif //__MOVEALGORITHM_H__
