#pragma once

#ifndef __GAMERULES_H__
#define __GAMERULES_H__

#include "Mediator.h"
#include <iostream>
#include <vector>

class GameRules: public GameMediator{
public:
	GameRules(std::vector<GameMediatorComponent*> comp) : 
		components(comp), GameMediator() {};

	void notify(Event evt) override;
	void notifyPlayerPosition(Position& playerPos) override;

private:
	std::vector<GameMediatorComponent*> components;

	void notifyAll(Event evt);
};

#endif // __GAMERULES_H__

