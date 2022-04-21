#pragma once

#include "Opponent.h"
#include "Player.h"
#include "RandMove.h"
#include "Astar/AstarMovement.h"
#include "MapManager.h"
#include "Mediator.h"
#include "ConfigLoader.h"
#include "Timer.h"
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
	void notifyPlayerPosition(const Position& pos) override;


private:
	int numberOfOpponents{};
	std::vector<Opponent> ops;
	float opponentSpeed{};
	
	using MoveAlgNormal = RandMove;
	using MoveAlgCatched = AstarMovement;
	Position opponentBase{1,1};

	const double disableTime = 2.5;
	// % of normal disable (rest of time should be indicated in some way)
	const double normalDisableTime = 0.75 * disableTime;
	const double warningDisableTime = disableTime - normalDisableTime;
	double currentGhostDisableTime = 0;

	Timer additionalDisableTimer{};
	Timer mainDisableTimer{};

	void setGhostDisableTimer();
	void nearEnableAllCb();
	void enableAllTimerCb();

	void createOpponents();
	Position getRandPosition();
	std::vector<Opponent>::iterator isPlayerPosReached(const Position& pos);
	void restartAll();
};
