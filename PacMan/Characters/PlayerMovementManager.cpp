#include "PlayerMovementManager.h"

PlayerMovementManager::PlayerMovementManager(Position& startPos, CoordType speed){
	lastPosition = startPos;
	currentDir = Direction::EAST;
	nextDir = Direction::EAST;
	moveTool.setStepSize(speed);
}

void PlayerMovementManager::keyActionCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	switch (key) {
	case GLFW_KEY_UP:
		tryMove(Direction::NORTH);
		break;
	case GLFW_KEY_DOWN:
		tryMove(Direction::SOUTH);
		break;
	case GLFW_KEY_LEFT:
		tryMove(Direction::WEST);
		break;
	case GLFW_KEY_RIGHT:
		tryMove(Direction::EAST);
		break;

	default:
		break;
	}
}

void PlayerMovementManager::getNextPosition(Position& pos){
	if (!isFirst) {
		lastPosition = pos;
		moveTool.moveInDir(pos, nextDir);
		if (isMoving(pos)) {
			currentDir = nextDir;
		}
		else {
			moveTool.moveInDir(pos, currentDir);
		}
	}
}

void PlayerMovementManager::setStepResolution(CoordType res){
	moveTool.setStepSize(res);
}

void PlayerMovementManager::tryMove(Direction dir){
	if (isFirst) {
		currentDir = dir;
		nextDir = dir;
		isFirst = false;
	}

	if (currentDir != dir) {
		nextDir = dir;
	}
}

bool PlayerMovementManager::isMoving(Position& posAfterUpdate){
	return lastPosition == posAfterUpdate;

}
