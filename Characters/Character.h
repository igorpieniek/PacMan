#pragma once

#include "Position.h"

class Character{
public:
	Position getPosition()const { return currentPostion; };
	void restoreInitialPosition() { currentPostion = initPositionSnapshot; };
	void stopMotion() { isMotionBlocked = true; };
	void unblockMotion() { isMotionBlocked = false; };

	virtual void update() = 0;
	
	virtual ~Character() {};

protected:
	Character( Position startPos) : currentPostion(startPos),
								    initPositionSnapshot(startPos),
									isMotionBlocked(false){};
	
	Position currentPostion;
	Position initPositionSnapshot;
	bool isMotionBlocked;
};