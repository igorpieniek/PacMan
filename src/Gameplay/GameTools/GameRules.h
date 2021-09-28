#pragma once

#include "Mediator.h"
#include "Timer.h"
#include <iostream>
#include <vector>
#include "ConfigLoader.h"


class GameRules: public GameMediator{
public:
	GameRules(std::vector<std::shared_ptr<GameMediatorComponent>> comp);

	void notify(Event evt) override;
	void notifyPlayerPosition(Position& playerPos) override;

private:
	std::vector<std::shared_ptr<GameMediatorComponent>> components;
	int startDelay = CONFIG.getStartDelay_s();
	const double disableTime = 2.5;
	// % of normal disable (rest of time should be indicated in some way)
	const double normalDisableTime  = 0.75 * disableTime;
	const double warningDisableTime = disableTime - normalDisableTime;
	double currentGhostDisableTime = 0;

	Timer smallOpponentEnableTimer{};
	Timer mainOpponentEnableTimer{};
	Timer motionTimer{};


	void notifyAll(Event evt);
	void setComponentsMediator();

	void disableMotionForTime(double secounds);
	void enableMotionCb();

	void reset();

	void setGhostDisableTimer();
	void nearEnableOpponentCb();
	void enableOpponentCb();
};
