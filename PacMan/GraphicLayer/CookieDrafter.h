#pragma once

#include "Drafter.h"

class CookieDrafter :public Drafter{
public:
	void draw(Position pos, Direction dir) override;
	void setSpecialPoint() { isSpecialPoint = true; };
private:
	bool isSpecialPoint = false;
};

