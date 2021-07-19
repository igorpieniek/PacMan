#pragma once


#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"
#include "MapManager.h"
#include "SafeMovement.h"
#include "Mediator.h"
#include <string>
#include <iostream>


class Player :public Character, public GameMediatorComponent{
public:
	Player(Position startPos, CoordType sp) :
		Character(startPos), moveTool(sp), prevPos(startPos), currentDir(Direction::EAST){};

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	const Position& getProviousPosition()const { return prevPos; };
	Direction getCurrentDirection()const { return currentDir; };

	int getAmountOfLifes()const { return numberOfLifes; };

	void notify(Event evt) override;

	//unused but have to exist
	void notifyPlayerPosition(Position& playerPos) override {};

private:
	SafeMovement moveTool;

	Direction currentDir;
	Position prevPos;

	int numberOfLifes = 3;

	void updatePrevPosAndDir(Position& suspectPos, Position& current, Direction dir);
	void update() override {}; // in private to delete
};

#endif //__PLAYER_H__

