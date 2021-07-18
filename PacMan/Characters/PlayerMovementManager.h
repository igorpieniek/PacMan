#pragma once

#include "Player.h"
#include "Movement.h"
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class PlayerMovementManager{
public:
	PlayerMovementManager(std::shared_ptr<Player> pl) : player(pl) 
	{
		lastPosition = pl->getPosition();
		currentDir = Direction::EAST;
		nextDir = Direction::EAST;
	};

	void keyActionCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void update();
private:
	std::shared_ptr<Player> player;

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

