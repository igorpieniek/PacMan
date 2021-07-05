#pragma once

#ifndef __OPONENTMANAGER_H__
#define __OPONENTMANAGER_H__

#include "Oponent.h"
#include "Player.h"
#include "RandMove.h"
#include "MapManager.h"
#include "Mediator.h"
#include <vector>
#include <map>
#include <cstdlib>
#include <iostream>


class OponentManager: public GameMediatorComponent{
public:
	
	OponentManager(int numberOfOps = { 4 }) : numberOfOponents(numberOfOps) 
	{
		createOponents();
	};

	void updateAll();
	void drawAll();
	void deactivateAll();
	void activeteAll();
	std::shared_ptr<Oponent> getOponent(int index);


	bool isOponentsAndDraw(Position& pos); //temporary to see results

	void notify(Event evt) override;
	void notifyPlayerPosition(Position& pos) override;


private:
	int numberOfOponents;
	std::vector<Oponent> ops;
	bool active = true;
	
	using MoveAlg = RandMove;

	void createOponents();
	Position getRandPosition();
	bool isPlayerPosReached(Position& pos);


};

#endif //__OPONENTMANAGER_H__
