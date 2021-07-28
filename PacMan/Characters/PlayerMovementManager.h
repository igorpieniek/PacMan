#pragma once

#include "Player.h"
#include "Movement.h"
#include "MoveAlgorithm.h"
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class PlayerMovementManager: public MoveAlgorithm{
public:
	PlayerMovementManager(Position& startPos);

	void keyActionCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void getNextPosition(Position& current) override;
	void setStepResolution(CoordType res) override;
private:

	typedef void (Player::*PlayerMethod)(void);

	std::unordered_map<Direction, PlayerMethod> dirMethod{
		{Direction::NORTH, &Player::moveUp },
		{Direction::EAST,  &Player::moveRight },
		{Direction::SOUTH, &Player::moveDown },
		{Direction::WEST, &Player::moveLeft }
	};

	bool isFirst = true;
	Position lastPosition;
	Direction currentDir;
	Direction nextDir;

	void tryMove(Direction dir);
	void updateLastPos();
	bool isMoving();
};

