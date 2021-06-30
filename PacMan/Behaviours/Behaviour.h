#pragma once

#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include "MoveAlgorithm.h"
#include "Position.h"

class Behaviour{
public:
	Behaviour(MoveAlgorithm* malg): moveAlg(malg) {};

	void move(Position& pos);
	void setStepSpeed(CoordType speed);

private:
	MoveAlgorithm* moveAlg;

};

#endif // __BEHAVIOUR_H__
