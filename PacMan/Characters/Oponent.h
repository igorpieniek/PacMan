#pragma once

#ifndef __OPONENT_H__
#define __OPONENT_H__

#include <iostream>
#include <string>
#include "Character.h"
#include "Behaviour.h"
#include "Position.h"

class Oponent: public Character{
public:
	Oponent(Position startPos, Behaviour* beh, CoordType speed) :
		Character(startPos), behaviour(beh)
	{
		behaviour->setStepSpeed(speed);
	};


	void update() override;


	void disable();
	void enable();

private:
	bool active = true;
	Behaviour* behaviour;
};

#endif // __OPONENT_H__