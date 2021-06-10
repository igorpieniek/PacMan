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
	
	OponentManager(int numberOfOps = { 4 }) : numberOfOponents(numberOfOps) {};

	void updateAll();
	void drawAll();

	bool checkOponentsAndDraw(Position& pos); //temporary to see results

private:
	int numberOfOponents;
	std::vector<Oponent> ops;
	
	using MoveAlg = RandMove;

	struct Algorithm_Beh {
		MoveAlg alg;
		Behaviour beh;
	};

	std::vector<Algorithm_Beh> algbeh;

	void createOponents();
	Position getRandPosition();

};

#endif //__OPONENTMANAGER_H__
