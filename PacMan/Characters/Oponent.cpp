#include "Oponent.h"



void Oponent::update(){
	behaviour->getNextPosition(currentPostion);
}

void Oponent::disable(){
	active = false;
}

void Oponent::enable(){
	active = true;
}
