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
		Direction currOpposite = getOpprositeDirection(currentDir);
		if (nextDir == currentDir || nextDir == currOpposite) {
			meth = dirMethod[nextDir];
			(*player.*meth)();
		}
		else if(player->getPosition().isIntPos()) {
			meth = dirMethod[nextDir];
			(*player.*meth)();
		}
		
		

		updateLastPos();
		if (isMoving()) {
			currentDir = nextDir;
		}
		else {
			meth = dirMethod[currentDir];
			(*player.*meth)();
		}

	}
	updateLastPos();
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
	return lastPosition == player->getPosition();
}
