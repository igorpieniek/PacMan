#pragma once

#include <iostream>
#include <string>
#include "Character.h"
#include "MoveAlgorithm.h"
#include "Position.h"

class Opponent: public Character{
public:
	Opponent(Position startPos, std::shared_ptr<MoveAlgorithm> beh ) :
		Character(startPos), behaviour(beh){};

	void update() override;

	void disable();
	void enable();

private:
	bool active = true;
	std::shared_ptr<MoveAlgorithm> behaviour;
};