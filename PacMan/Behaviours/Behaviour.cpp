#include "Behaviour.h"

void Behaviour::move(Position& pos){
	pos = moveAlg->getNextPosition(pos);
}

void Behaviour::setStepSpeed(int speed){
	moveAlg->setStepResolution(speed);
}
