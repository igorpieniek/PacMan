#pragma once

#ifndef __OPONENTMANAGER_H__
#define __OPONENTMANAGER_H__

#include "Oponent.h"
#include "Player.h"
#include "RandMove.h"
#include "MapManager.h"
#include <vector>
#include <map>
#include <cstdlib>


class OponentManager{
public:
	
	OponentManager(int numberOfOps = { 4 }) : numberOfOponents(numberOfOps) 
	{
		createOponents();
	};

	void updateAll();
	void drawAll();

	bool isOponentsAndDraw(Position& pos); //temporary to see results

private:
	int numberOfOponents;
	std::vector<Oponent> ops;
	
	using MoveAlg = RandMove;

	void createOponents();
	Position getRandPosition();


};

#endif //__OPONENTMANAGER_H__
