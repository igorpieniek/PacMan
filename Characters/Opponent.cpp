#include "Opponent.h"

void Opponent::update(){
	if (isMotionBlocked) return;
	if (behaviour) {
		behaviour->update(currentPostion);
	}
	else {
		throw std::runtime_error("Opponent: No behaviour algorithm added!");
	}
}

void Opponent::disable(){
	active = false;
}

void Opponent::enable(){
	active = true;
}
