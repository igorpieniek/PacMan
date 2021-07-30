#pragma once

#include "Mediator.h"
#include <iostream>
#include <vector>
#include <windows.h>

class GameRules: public GameMediator{
public:
	GameRules(std::vector<GameMediatorComponent*> comp);

	void notify(Event evt) override;
	void notifyPlayerPosition(Position& playerPos) override;

	void update();

private:
	std::vector<GameMediatorComponent*> components;

	void notifyAll(Event evt);
	void setComponentsMediator();
};

