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
	void notifyPlayerPosition(const Position& playerPos) override;

private:
	std::vector<std::shared_ptr<GameMediatorComponent>> components;
	int startDelay = CONFIG.getStartDelay_s();

	Timer smallOpponentEnableTimer{};
	Timer mainOpponentEnableTimer{};
	Timer motionTimer{};


	void notifyAll(Event evt);
	void setComponentsMediator();

	void disableMotionForTime(double secounds);
	void enableMotionCb();

	void reset();
};

