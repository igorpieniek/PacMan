#pragma once

#include <iostream>
#include <string>
#include "Character.h"
#include "MoveAlgorithm.h"
#include "Position.h"

class Opponent: public Character{
public:
	Opponent() :Character({}) {};

	void setStartPosition(Position&& pos);
	void setMoveAlgorithm(std::unique_ptr<MoveAlgorithm>&& beh);

	void update() override;

	void disable();
	void enable();

private:
	bool active = true;
	std::unique_ptr<MoveAlgorithm> behaviour{};
};