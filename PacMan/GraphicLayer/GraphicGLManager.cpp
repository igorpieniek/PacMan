#include "GraphicGLManager.h"
#include <iostream>

GraphicGLManager::GraphicGLManager(
		const std::shared_ptr<PointsManager> pointsManag,
		const std::shared_ptr<Player> pl,
		const std::shared_ptr<OponentManager> oponentManag)
		: GraphicManagerInterface(pointsManag, pl, oponentManag)
{

	Render2D::instance().init();

	for (int i = 0; i < oponents->getAmountOfOponents(); i++) {
		ghosts.push_back({});
		ghosts.back().addImage(getnextGhostPath());
	}

	plDrafter.addImage(playerPath);
	cookieDrafter.addImage(cookiePath);
	heartDrafter.addImage(heartPath);

	mapDrafter.addImage(mapPath);

}

void GraphicGLManager::draw(){
	mapDrafter.draw();

	drawCookies();
	drawPlayer();
	drawGhosts();
	drawHealth();
	drawPointsCounter();

	drawStartMenuProcess();
	drawStartCounterProcess();
	drawFinishMenuProcess();

	Render2D::instance().process();
}


void GraphicGLManager::drawCookies(){
	for (const auto& cookie : points->getPointsData()) {
		if (cookie.getPointClass() == PointCat::SPECIAL) {
			cookieDrafter.setSpecialPoint();
		}
		cookieDrafter.draw(cookie, Direction::EAST);
	}
}

void GraphicGLManager::drawPointsCounter(){
	counterDrafter.setValue(points->getPoints());
}

void GraphicGLManager::drawStartMenuProcess(){
	if (!isStartButtonPressed) {
		if (startMenu.drawAndGetStatus()) {
			 isStartButtonPressed = true;
			 mediator->notify(Event::START_GAME);
			 startCounter.start();
		}
	}
}

void GraphicGLManager::drawFinishMenuProcess(){
	if (isRetryButtonPressed) {
		if (finishMenu.drawAndGetStatus(points->isAllPointsReached(),
										points->getPoints())) {
			isRetryButtonPressed = false;
			mediator->notify(Event::RESET_GAME);
			mediator->notify(Event::START_GAME);
			startCounter.start();
		}
	}
}

void GraphicGLManager::drawStartCounterProcess(){
	if (!isRetryButtonPressed)
			startCounter.draw();
}


void GraphicGLManager::drawPlayer(){
	plDrafter.updateIsMoving(player->isMoving());
	plDrafter.draw(player->getPosition(), player->getCurrentDirection());
}

void GraphicGLManager::drawGhosts(){
	for (int i = 0; i < oponents->getAmountOfOponents(); i++) {
		std::shared_ptr<Oponent> opPos = oponents->getOponent(i);
		ghosts[i].draw(opPos->getPosition(), Direction::EAST);
	}
}

void GraphicGLManager::drawHealth(){
	Position pos{2 , MapManager::instance().getMapYSize() };
	Movement moveTool(3);
	for (int i = 0; i < player->getAmountOfLifes(); i++) {
		heartDrafter.draw(pos, Direction::EAST);
		moveTool.moveRight(pos);
	}
}

std::string GraphicGLManager::getnextGhostPath(){
	static size_t counter;
	if (counter >= ghostPaths.size()) {
		counter = 0;
	}
	return ghostPaths[counter++];
}


void GraphicGLManager::notify(Event evt) {
	switch (evt){
	case Event::END_OF_LIVES:
	case Event::ALL_POINTS_COLLECTED:
		isRetryButtonPressed = true;
		break;

	case Event::RESTART_POSITIONS:
		startCounter.start();
		break;

	default:
		break;
	}
}
