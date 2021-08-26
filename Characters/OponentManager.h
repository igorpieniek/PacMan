#pragma once

#include "Oponent.h"
#include "Player.h"
#include "RandMove.h"
#include "MapManager.h"
#include "Mediator.h"
#include "ConfigLoader.h"
#include <vector>
#include <map>
#include <cstdlib>
#include <iostream>
#include <algorithm>


class OponentManager: public GameMediatorComponent{
public:
	
	OponentManager(int numberOfOps = { 4 });

	void updateAll();
	void deactivateAll();
	void activeteAll();
	std::shared_ptr<Oponent> getOponent(int index);
	int getAmountOfOponents()const { return numberOfOponents; };

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