#pragma once

#include "Drafter.h"
#include "CellPoint.h"

class CookieDrafter :public Drafter{
public:
	void draw(Position pos, Direction dir = Direction::EAST) override;
	void setSpecialPoint() { isSpecialPoint = true; };
private:
	bool isSpecialPoint = false;
};

