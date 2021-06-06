#pragma once

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Position.h"

class Character{
public:
	using SpeedType = int;
	Position getPosition()const { return currentPostion; };
	void setPosition(Position& pos) { currentPostion = pos; };

	virtual void draw() = 0;
	virtual ~Character() {};

protected:
	Character(SpeedType s, Position startPos) : speed(s), currentPostion(startPos) {};
	SpeedType speed;
	Position currentPostion;


};

#endif

