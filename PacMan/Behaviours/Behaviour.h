#pragma once

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