#pragma once
#include "Drafter.h"

class HeartDrafter :public Drafter{
public:
	void draw(Position pos, Direction dir = Direction::EAST) override;
	void setNumberOfLives(int lives);
private:
	int currentNumberOfLives = 0;
};

