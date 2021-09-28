#pragma once

#include <iostream>
#include <string>
#include "Character.h"
#include "MoveAlgorithm.h"
#include "Position.h"

class Opponent: public Character{
public:
	Opponent() :Character({}) {};
	enum class Mode {
		ACTIVE, DISABLE, DEFEATED
	};
	void setStartPosition(Position&& pos);
	void setMoveAlgorithm(std::unique_ptr<MoveAlgorithm>&& beh);

	void update() override;

	void setState(Mode m) { mode = m; };
	Mode getState()const { return mode; };

private:
	Mode mode{Mode::ACTIVE};
	std::unique_ptr<MoveAlgorithm> behaviour{};
};