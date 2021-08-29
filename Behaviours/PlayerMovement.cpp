#include "PlayerMovement.h"

PlayerMovement::PlayerMovement(CoordType speed){
	currentDir = Direction::EAST;
	nextDir = Direction::EAST;
	setStepResolution(speed);
}

void PlayerMovement::keyActionCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
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

void PlayerMovement::update(Position& pos){
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

void PlayerMovement::setStepResolution(CoordType res){
	if (res < 0.0f || res > 1.0f) {
		throw std::runtime_error("PlayerMovement: player speed must be from range <0,1> your value: " + std::to_string(res));
	}
	moveTool.setStepSize(res);
}

void PlayerMovement::reset(){
	isFirst = true;
}


void PlayerMovement::tryMove(Direction dir){
	if (isFirst) {
		currentDir = dir;
		nextDir = dir;
		isFirst = false;
	}

	if (currentDir != dir) {
		nextDir = dir;
	}
}

bool PlayerMovement::isMoving(Position& posAfterUpdate){
	return posAfterUpdate.distance(lastPosition) > 0.001f;

}
