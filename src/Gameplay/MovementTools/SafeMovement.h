#pragma once

#include "MapManager.h"
#include "Movement.h"


class SafeMovement : public Movement {
public:
	SafeMovement(CoordType step = { 1 }) :
		Movement(step) {};

	void moveUp(Position& pos) override;
	void moveDown(Position& pos) override;
	void moveLeft(Position& pos) override;
	void moveRight(Position& pos) override;

	void moveInDir(Position& pos, Direction dir) override;

	bool isNextPositionFree(const Position& pos, Direction dir);

private:
	bool isMoveInDirAllowed(const Position& pos, Direction dir);
	void moveInDirDanger(Position& pos, Direction dir);

	Movement tempDangerMoveTool;
};
