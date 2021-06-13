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
	Player(Position startPos, SpeedType sp, std::string sym = { "p" }) :
		Character(startPos), moveTool(sp), symbol(sym){};

	void draw() override;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	int getAmountOfLifes()const { return numberOfLifes; };

	void notify(Event evt) override;

	//unused but have to exist
	void notifyPlayerPosition(Position& playerPos) override {};

private:
	std::string symbol;
	SafeMovement moveTool;

	int numberOfLifes = 3;

	void update() override {}; // in private to delete
};

#endif //__PLAYER_H__

