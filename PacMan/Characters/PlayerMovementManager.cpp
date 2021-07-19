#include "PlayerMovementManager.h"

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

void PlayerMovementManager::update(){
	if (!isFirst) {
		PlayerMethod meth;
		updateLastPos();
		meth = dirMethod[nextDir];
		(*player.*meth)();
		if (isMoving()) {
			currentDir = nextDir;
		}
		else {
			meth = dirMethod[currentDir];
			(*player.*meth)();
		}
	}
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

void PlayerMovementManager::updateLastPos(){
	lastPosition = player->getPosition();
}

bool PlayerMovementManager::isMoving(){
	return player->getPosition().distance(lastPosition) > 0.001f;
}
