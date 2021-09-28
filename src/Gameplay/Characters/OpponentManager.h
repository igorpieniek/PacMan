#pragma once

#include "Opponent.h"
#include "Player.h"
#include "RandMove.h"
#include "Astar/AstarMovement.h"
#include "MapManager.h"
#include "Mediator.h"
#include "ConfigLoader.h"
#include <vector>
#include <map>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>


class OpponentManager: public GameMediatorComponent{
public:
	
	OpponentManager(float speed, int numberOfOps = { 4 });

	void updateAll();
	void deactivateAll();
	void activeteAll();
	Position getOpponentXposition(int index);
	Opponent::Mode getOpponentXmode(int index);
	int getAmountOfOpponents()const { return numberOfOpponents; };

	void notify(Event evt) override;
	void notifyPlayerPosition(Position& pos) override;


private:
	int numberOfOpponents{};
	std::vector<Opponent> ops;
	float opponentSpeed{};
	
	using MoveAlgNormal = RandMove;
	using MoveAlgCatched = AstarMovement;
	Position opponentBase{1,1};

	void createOpponents();
	Position getRandPosition();
	std::vector<Opponent>::iterator isPlayerPosReached(Position& pos);
	void restartAll();
};
