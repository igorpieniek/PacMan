#pragma once
#include "Drafter.h"

class PlayerDrafter : public Drafter{
public :
	virtual void draw(Position pos, Direction dir) override;
private:
	float currentAngle = 0.0f;
	float rotationStep = 2.0f; //deg
	float maxRotationAngle = 15.0f;
};

