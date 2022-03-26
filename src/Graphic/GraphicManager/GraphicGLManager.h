#pragma once
#include <algorithm>

#include "GraphicManager/GraphicManagerInterface.h"

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
	void notifyPlayerPosition(const Position& pos)override {};


	std::vector<std::string> ghostPaths = CONFIG.getOpponentsImgPaths();
	std::string disabledGhostPath = CONFIG.getDisabledOpponentImgPath();
	std::string defeatedGhostPath = CONFIG.getDefeatedOpponentImgPath();
	std::string ghostBasePath	  = CONFIG.getGhostBaseImgPath();
	const Position ghostBasePos = CONFIG.getGhostBasePosition();

	std::string mapPath	   = CONFIG.getDynamicMapImgPath();
	std::string playerPath = CONFIG.getPlayerImgPath();
	std::string cookiePath = CONFIG.getPointImgPath();
	std::string heartPath  = CONFIG.getHeartImgPath();


	std::vector<Drafter> ghosts;
	Drafter disabledGhost{};
	Drafter defeatGhost{};
	Drafter baseForGhosts{};
	bool disabledFlag = false;
	bool isNearEnabledFlag = false;

	PlayerDrafter plDrafter{};
	CookieDrafter cookieDrafter{};
	HeartDrafter heartDrafter{};

	MapDrafter mapDrafter{};

	PointCounter counterDrafter{};
	StartMenu startMenu{};
	StartCounter startCounter{};
	bool isStartButtonPressed = false;

	FinishMenu finishMenu{};
	bool isRetryButtonPressed = false;
	

	void drawCookies();
	void drawPointsCounter();
	void drawStartMenuProcess();
	void drawFinishMenuProcess();
	void drawStartCounterProcess();
	void drawPlayer();
	void drawGhosts();
	void drawBaseForGhosts();

	void rawDrawGhostsNearEnabledProcess();
	void rawDrawGhosts();
	void drawHealth();

	std::string getnextGhostPath();
};

