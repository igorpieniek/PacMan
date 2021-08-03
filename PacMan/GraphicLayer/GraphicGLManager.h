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
#include "ConfigLoader.h"

class GraphicGLManager :public GraphicManagerInterface, public GameMediatorComponent {
public:
	GraphicGLManager(const std::shared_ptr<PointsManager> pointsManag,
					 const std::shared_ptr<Player> pl,
					 const std::shared_ptr<OponentManager> oponentManag);

	void draw() override;
	void notify(Event evt) override;
private:
	void notifyPlayerPosition(Position& pos)override {};

	std::vector<std::string> ghostPaths = ConfigLoader::instance().getOponentsImgPaths();
	std::string mapPath	 = ConfigLoader::instance().getDynamicMapImgPath();
	std::string playerPath = ConfigLoader::instance().getPlayerImgPath();
	std::string cookiePath = ConfigLoader::instance().getPointImgPath();
	std::string heartPath  = ConfigLoader::instance().getHeartImgPath();


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

