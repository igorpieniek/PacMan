#pragma once


#include "Player.h"
#include "OponentManager.h"
#include "DrawInterface.h"

class DrawManager{
public:
	DrawManager(DrawInterfaceFactory* drawFactor) : factor(drawFactor) {};
	void addPlayer(const Player* pl) { player = pl; };
	void addOponentManager(const OponentManager* op) { oponentManager = op; };

private:
	const Player* player = nullptr;
	const OponentManager* oponentManager = nullptr;
	DrawInterfaceFactory* factor;
};

