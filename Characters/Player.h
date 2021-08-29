#pragma once

#include "Character.h"
#include "MapManager.h"
#include "SafeMovement.h"
#include "Mediator.h"
#include "MoveAlgorithm.h"
#include <string>
#include <iostream>


class Player :public Character, public GameMediatorComponent{
public:
	Player(Position startPos, std::shared_ptr<MoveAlgorithm> moveAlg);

	void notify(Event evt) override;
	void update() override;

	Direction getCurrentDirection()const { return currentDir; };
	bool isMoving()const { return is_moving; };

	int getAmountOfLifes()const { return numberOfLifes; };

	//unused but have to exist
	void notifyPlayerPosition(Position& playerPos) override {};

private:
	std::shared_ptr<MoveAlgorithm> moveManag;
	Direction currentDir;
	Position prevPos;
	bool is_moving = false;

	int numberOfLifes = 3; //add to config loader

	void updatePrevPosAndDir(Position& suspectPos, Position& current);
	 
};

