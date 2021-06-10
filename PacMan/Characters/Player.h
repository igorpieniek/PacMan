#pragma once


#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"
#include "MapManager.h"
#include "SafeMovement.h"
#include <string>
#include <iostream>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class Player :public Character{
public:
	Player(Position startPos, SpeedType sp, std::string sym = { "p" }) :
		Character(startPos), moveTool(sp), symbol(sym){};

	void draw() override;

private:
	std::string symbol;
	SafeMovement moveTool;

	int numberOfLives = 3;
	int numberOfPoints = 0;

	void update() override {}; // in private to delete
};

#endif //__PLAYER_H__

