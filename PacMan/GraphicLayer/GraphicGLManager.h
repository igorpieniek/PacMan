#pragma once
#include "GraphicManagerInterface.h"
#include "Render2D.h"
#include "Drafter.h"
#include "MapManager.h"

#include "PlayerDrafter.h"
#include "CookieDrafter.h"

#include "MapDrafter.h"

#include <algorithm>

class GraphicGLManager :public GraphicManagerInterface{
public:
	GraphicGLManager(const std::shared_ptr<PointsManager> pointsManag,
					 const std::shared_ptr<Player> pl,
					 const std::shared_ptr<OponentManager> oponentManag);

	void draw() override;
private:

	const std::vector<std::string> ghostPaths = { //TODO: move to module that read that files from JSON file
		"images/ghost1.png",
		"images/ghost2.png",
		"images/ghost3.png",
		"images/ghost4.png",
	};

	const std::string mapPath = "images/newMap.png";

	const std::string playerPath = "images/pacman.png";

	const std::string cookiePath = "images/point.png";


	std::vector<Drafter> ghosts;
	std::vector<MapCell> mapvec;
	PlayerDrafter plDrafter;
	CookieDrafter cookieDrafter;
	float scale;

	void drawObstacles();
	MapDrafter mapDrafter;


	std::string getnextGhostPath();
};

