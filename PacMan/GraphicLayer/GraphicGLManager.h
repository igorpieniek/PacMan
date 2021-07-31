#pragma once
#include "GraphicManagerInterface.h"
#include "Mediator.h"
#include "Render2D.h"
#include "Drafter.h"
#include "MapManager.h"

#include "PlayerDrafter.h"
#include "CookieDrafter.h"
#include "HeartDrafter.h"

#include "MapDrafter.h"
#include "Movement.h"
#include <algorithm>

class GraphicGLManager :public GraphicManagerInterface, public GameMediatorComponent {
public:
	GraphicGLManager(const std::shared_ptr<PointsManager> pointsManag,
					 const std::shared_ptr<Player> pl,
					 const std::shared_ptr<OponentManager> oponentManag);

	void draw() override;
	void notify(Event evt) override;
private:
	void notifyPlayerPosition(Position& pos)override {};

	const std::vector<std::string> ghostPaths = { //TODO: move to module that read that files from JSON file
		"images/ghost1.png",
		"images/ghost2.png",
		"images/ghost3.png",
		"images/ghost4.png",
	};

	const std::string mapPath = "images/newMap.png";

	const std::string playerPath = "images/pacman.png";

	const std::string cookiePath = "images/point.png";

	const std::string heartPath = "images/heart.png";


	std::vector<Drafter> ghosts;
	std::vector<MapCell> mapvec;
	PlayerDrafter plDrafter;
	CookieDrafter cookieDrafter;
	HeartDrafter heartDrafter;

	void drawCookies();
	void drawPlayer();
	void drawGhosts();
	void drawHealth();
	MapDrafter mapDrafter;


	std::string getnextGhostPath();
};

