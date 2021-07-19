#pragma once

#include "Position.h"
#include "Movement.h"
#include "Player.h"
#include "OponentManager.h"
#include "MapManager.h"
#include "PointsManager.h"


class GraphicManagerInterface{
public:
	GraphicManagerInterface(
		const std::shared_ptr<PointsManager> pointsManag,
		const std::shared_ptr<Player> pl,
		const std::shared_ptr<OponentManager> oponentManag)
		:points(pointsManag), player(pl), oponents(oponentManag) {};

	virtual void draw() = 0;

protected:
	const std::shared_ptr<PointsManager> points;
	const std::shared_ptr<Player> player;
	const std::shared_ptr<OponentManager> oponents;
};

