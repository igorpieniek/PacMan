#pragma once

#ifndef __GAMERULES_H__
#define __GAMERULES_H__

#include "Mediator.h"
#include <vector>

class GameRules: public GameMediator{
public:
	GameRules(std::vector<GameMediatorComponent*> comp) : 
		components(comp), GameMediator() {};

	void notify(Event evt) override;
	void notifyPlayerPosition(Position& playerPos) override;

private:
	std::vector<GameMediatorComponent*> components;
};

#endif // __GAMERULES_H__

