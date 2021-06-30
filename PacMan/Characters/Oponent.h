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
	Oponent(Position startPos, Behaviour* beh, CoordType speed, std::string sym = {"q"}) :
		Character(startPos), behaviour(beh), symbol(sym) 
	{
		behaviour->setStepSpeed(speed);
	};


	void draw() override;
	void update() override;


	void disable();
	void enable();

private:
	bool active = true;
	Behaviour* behaviour;
	std::string symbol;
};

#endif // __OPONENT_H__