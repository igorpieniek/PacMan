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
	const double disableTime = 2.0;
	// % of normal disable (rest of time should be indicated in some way)
	const double normalDisablePercentage = 0.75; 

	void notifyAll(Event evt);
	void setComponentsMediator();

	void disableMotionForTime(double secounds);
	void enableMotionCb();


	void nearEnableOpponentCb();
	void enableOpponentCb();
};

