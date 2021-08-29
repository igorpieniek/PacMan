#pragma once
#include <algorithm>

#include "GraphicManagerInterface.h"

#include "Mediator.h"
#include "Render2D.h"
#include "Movement.h"
#include "MapManager.h"
#include "ConfigLoader.h"

#include "Drafters/Drafter.h"
#include "Drafters/PlayerDrafter.h"
#include "Drafters/CookieDrafter.h"
#include "Drafters/HeartDrafter.h"
#include "Drafters/MapDrafter.h"

#include "Menu/PointCounter.h"
#include "Menu/StartMenu.h"
#include "Menu/FinishMenu.h"
#include "Menu/StartCounter.h"

class GraphicGLManager :public GraphicManagerInterface, public GameMediatorComponent {
public:
	GraphicGLManager(const std::shared_ptr<PointsManager> pointsManag,
					 const std::shared_ptr<Player> pl,
					 const std::shared_ptr<OpponentManager> opponentManag);

	void draw() override;
	void notify(Event evt) override;
private:
	void notifyPlayerPosition(Position& pos)override {};


	std::vector<std::string> ghostPaths = CONFIG.getOpponentsImgPaths();
	std::string disabledGhostPath = CONFIG.getDisabledOpponentImgPath();

	std::string mapPath	 = CONFIG.getDynamicMapImgPath();
	std::string playerPath = CONFIG.getPlayerImgPath();
	std::string cookiePath = CONFIG.getPointImgPath();
	std::string heartPath  = CONFIG.getHeartImgPath();


	std::vector<Drafter> ghosts;
	Drafter disabledGhost;
	bool disabledFlag = false;
	bool isNearEnabledFlag = false;

	std::vector<MapCell> mapvec;
	PlayerDrafter plDrafter;
	CookieDrafter cookieDrafter;
	HeartDrafter heartDrafter;

	PointCounter counterDrafter;
	StartMenu startMenu;
	StartCounter startCounter;
	bool isStartButtonPressed = false;

	FinishMenu finishMenu;
	bool isRetryButtonPressed = false;
	

	void drawCookies();
	void drawPointsCounter();
	void drawStartMenuProcess();
	void drawFinishMenuProcess();
	void drawStartCounterProcess();
	void drawPlayer();
	void drawGhosts();
	void rawDrawGhostsEnabled();
	void rawDrawGhostsDisabled();
	void drawHealth();
	MapDrafter mapDrafter;


	std::string getnextGhostPath();
};

