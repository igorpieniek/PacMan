#include "Oponent.h"

void Oponent::update(){
	if (isMotionBlocked) return;
	behaviour->update(currentPostion);
}

void Oponent::disable(){
	active = false;
}

void Oponent::enable(){
	active = true;
}
