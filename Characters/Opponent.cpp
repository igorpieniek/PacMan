#include "Opponent.h"

void Opponent::update(){
	if (isMotionBlocked) return;
	behaviour->update(currentPostion);
}

void Opponent::disable(){
	active = false;
}

void Opponent::enable(){
	active = true;
}
