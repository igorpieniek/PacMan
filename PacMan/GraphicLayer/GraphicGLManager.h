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
#include "Menu/PointCounter.h"

class GraphicGLManager :public GraphicManagerInterface, public GameMediatorComponent {
public:
	GraphicGLManager(const std::shared_ptr<PointsManager> pointsManag,
					 const std::shared_ptr<Player> pl,
					 const std::shared_ptr<OponentManager> oponentManag);

	void draw() override;
	void notify(Event evt) override;
private:
	void notifyPlayerPosition(Position& pos)override {};

	std::vector<std::string> ghostPaths = CONFIG.getOponentsImgPaths();
	std::string mapPath	 = CONFIG.getDynamicMapImgPath();
	std::string playerPath = CONFIG.getPlayerImgPath();
	std::string cookiePath = CONFIG.getPointImgPath();
	std::string heartPath  = CONFIG.getHeartImgPath();


	std::vector<Drafter> ghosts;
	std::vector<MapCell> mapvec;
	PlayerDrafter plDrafter;
	CookieDrafter cookieDrafter;
	HeartDrafter heartDrafter;

	PointCounter counterDrafter;

	void drawCookies();
	void drawPlayer();
	void drawGhosts();
	void drawHealth();
	MapDrafter mapDrafter;


	std::string getnextGhostPath();
};

