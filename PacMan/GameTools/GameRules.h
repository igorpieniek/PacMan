#pragma once

#include "Mediator.h"
#include <iostream>
#include <vector>

class GameRules: public GameMediator{
public:
	GameRules(std::vector<GameMediatorComponent*> comp) : 
		components(comp), GameMediator() 
	{
		setComponentsMediator();
	};

	void notify(Event evt) override;
	void notifyPlayerPosition(Position& playerPos) override;

private:
	std::vector<GameMediatorComponent*> components;

	void notifyAll(Event evt);
	void setComponentsMediator();
};

