#pragma once


#include "Player.h"
#include "OponentManager.h"
#include "DrawInterface.h"

#include <unordered_map>

class DrawManager{
public:
	DrawManager(std::shared_ptr<DrawInterface> playerDrafter, std::shared_ptr <DrawInterfaceFactory> oponentDrawFactor) :
		playerDrafter(playerDrafter), oponentDrafterFactor(oponentDrawFactor) {};
	void addPlayer(std::shared_ptr<Player> pl);
	void addOponentManager(std::shared_ptr<OponentManager> op);
	void drawAll();

private:
	std::shared_ptr<Player> player;
	std::shared_ptr<OponentManager> oponentManager = nullptr;
	std::shared_ptr<DrawInterfaceFactory> oponentDrafterFactor;
	std::shared_ptr<DrawInterface> playerDrafter;

	std::unordered_map<std::shared_ptr<Oponent>, std::shared_ptr<DrawInterface>> oponentDrafter;

};

