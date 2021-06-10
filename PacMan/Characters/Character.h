#pragma once

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Position.h"

class Character{
public:
	using SpeedType = int;
	Position getPosition()const { return currentPostion; };

	virtual void update() = 0;
	virtual void draw() = 0;
	
	virtual ~Character() {};

protected:
	Character( Position startPos) : currentPostion(startPos) {};

	Position currentPostion;

};

#endif

