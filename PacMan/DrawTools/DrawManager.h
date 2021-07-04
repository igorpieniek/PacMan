#pragma once


#include "Player.h"
#include "OponentManager.h"
#include "DrawInterface.h"

#include <unordered_map>

class DrawManager{
public:
	DrawManager(DrawInterface* playerDrafter, DrawInterfaceFactory* oponentDrawFactor) : 
		playerDrafter(playerDrafter), oponentDrafterFactor(oponentDrawFactor) {};
	void addPlayer(const Player* pl);
	void addOponentManager(OponentManager* op);
	void drawAll();

private:
	const Player* player = nullptr;
	OponentManager* oponentManager = nullptr;
	DrawInterfaceFactory* oponentDrafterFactor;
	DrawInterface* playerDrafter;

	std::unordered_map<Oponent*, DrawInterface*> oponentDrafter;

};

