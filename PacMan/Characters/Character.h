#pragma once

#include "Position.h"

class Character{
public:
	Position getPosition()const { return currentPostion; };
	void restoreInitialPosition() { currentPostion = initPositionSnapshot; };

	virtual void update() = 0;
	
	virtual ~Character() {};

protected:
	Character( Position startPos) : currentPostion(startPos),
								    initPositionSnapshot(startPos){};

	Position currentPostion;
	Position initPositionSnapshot;

};