#include "Oponent.h"

void Oponent::update(){
	behaviour->update(currentPostion);
}

void Oponent::disable(){
	active = false;
}

void Oponent::enable(){
	active = true;
}
