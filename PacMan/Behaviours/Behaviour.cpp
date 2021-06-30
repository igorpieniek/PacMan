#include "Behaviour.h"

void Behaviour::move(Position& pos){
	pos = moveAlg->getNextPosition(pos);
}

void Behaviour::setStepSpeed(CoordType speed){
	moveAlg->setStepResolution(speed);
}
