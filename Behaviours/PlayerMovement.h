#pragma once

#include "Player.h"
#include "Movement.h"
#include "MoveAlgorithm.h"
#include "SafeMovement.h"
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class PlayerMovement: public MoveAlgorithm{
public:
	PlayerMovement(CoordType speed);

	void keyActionCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void update(Position& current) override;
	void setStepResolution(CoordType res) override;
	void reset() override;

private:
	SafeMovement moveTool{};

	bool isFirst = true;
	Position lastPosition{};
	Direction currentDir{};
	Direction nextDir{};

	void tryMove(Direction dir);
	bool isMoving(Position& posAfterUpdate);
};

