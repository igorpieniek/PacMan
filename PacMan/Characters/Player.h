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
	Player(Position startPos, CoordType sp, std::shared_ptr<MoveAlgorithm> moveAlg) :
		Character(startPos), 
		prevPos(startPos), 
		currentDir(Direction::EAST),
		is_moving(false),
		moveManag(moveAlg)
	{
		moveManag->setStepResolution(sp);
	};



	const Position& getProviousPosition()const { return prevPos; };
	Direction getCurrentDirection()const { return currentDir; };
	bool isMoving()const { return is_moving; };

	int getAmountOfLifes()const { return numberOfLifes; };

	void notify(Event evt) override;

	//unused but have to exist
	void notifyPlayerPosition(Position& playerPos) override {};
	void update() override;

private:
	std::shared_ptr<MoveAlgorithm> moveManag;
	Direction currentDir;
	Position prevPos;
	bool is_moving;

	int numberOfLifes = 3;

	void updatePrevPosAndDir(Position& suspectPos, Position& current);
	 
};

