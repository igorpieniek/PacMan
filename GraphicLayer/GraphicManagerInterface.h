#pragma once

#include "Position.h"
#include "Movement.h"
#include "Player.h"
#include "OpponentManager.h"
#include "MapManager.h"
#include "PointsManager.h"


class GraphicManagerInterface{
public:
	GraphicManagerInterface(
		const std::shared_ptr<PointsManager> pointsManag,
		const std::shared_ptr<Player> pl,
		const std::shared_ptr<OpponentManager> opponentManag)
		:points(pointsManag), player(pl), opponents(opponentManag) {};

	virtual void draw() = 0;

protected:
	const std::shared_ptr<PointsManager> points;
	const std::shared_ptr<Player> player;
	const std::shared_ptr<OpponentManager> opponents;
};

