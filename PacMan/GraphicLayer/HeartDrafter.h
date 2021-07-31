#pragma once
#include "Drafter.h"

class HeartDrafter :public Drafter{
public:
	void draw(Position pos, Direction dir) override;
};

