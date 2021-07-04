#include "Oponent.h"



void Oponent::update(){
	behaviour->move(currentPostion);
}

void Oponent::disable(){
	active = false;
}

void Oponent::enable(){
	active = true;
}
