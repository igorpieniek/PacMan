#pragma once

#include "Position.h"
#include "Movement.h"
#include "Player.h"
#include "OponentManager.h"
#include "MapManager.h"


class GraphicManagerInterface{
public:
	GraphicManagerInterface(const std::shared_ptr<Player> pl,
		const std::shared_ptr<OponentManager> oponentManag)
		:player(pl), oponents(oponentManag) {};

	virtual void draw() = 0;

protected:
	const std::shared_ptr<Player> player;
	const std::shared_ptr<OponentManager> oponents;
};

