#include "PlayerMovementManager.h"

PlayerMovementManager::PlayerMovementManager(CoordType speed){
	currentDir = Direction::EAST;
	nextDir = Direction::EAST;
	setStepResolution(speed);
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
	return posAfterUpdate.distance(lastPosition) > 0.001f;

}
