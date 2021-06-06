#pragma once


#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"
#include "Movement.h"
#include "MapManager.h"
#include <string>
#include <iostream>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class Player :public Character{
public:
	Player(Position startPos, SpeedType sp, MapManager* mapmanag, std::string sym = { "p" }) :
		Character(sp, startPos), symbol(sym), mapManager(mapmanag)
	{
		moveTool.setStepSize(sp);
	};

	void draw() override;
	void update() override;


private:
	std::string symbol;
	Movement moveTool;
	MapManager* mapManager;

	int numberOfLives = 3;
	int numberOfPoints = 0;

	void move(Direction dir);
};

#endif //__PLAYER_H__

