#include "GraphicGLManager.h"
#include <iostream>

GraphicGLManager::GraphicGLManager(
		const std::shared_ptr<PointsManager> pointsManag,
		const std::shared_ptr<Player> pl,
		const std::shared_ptr<OpponentManager> opponentManag)
		: GraphicManagerInterface(pointsManag, pl, opponentManag)
{

	if (ghostPaths.size() == 0) {
		throw std::runtime_error("GraphicGLManager: No Opponent paths added!");
	}
	Render2D::instance().init();

	ghosts.reserve(opponents->getAmountOfOpponents());
	for (int i = 0; i < opponents->getAmountOfOpponents(); i++) {
		ghosts.push_back({});
		ghosts.back().addImage(getnextGhostPath());
	}
	disabledGhost.addImage(disabledGhostPath);
	defeatGhost.addImage(defeatedGhostPath);
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
		cookieDrafter.draw(cookie);
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

void GraphicGLManager::drawGhosts() {
	static int nearDisableEndCounter;
	constexpr int maxCnt = 5;
	if (isNearEnabledFlag) {
		nearDisableEndCounter++;
		if (nearDisableEndCounter < maxCnt) {
			rawDrawGhostsDisabled();
		}
		else {
			if (nearDisableEndCounter >= 2*maxCnt) nearDisableEndCounter = 0;
			rawDrawGhostsEnabled();
		}
	}
	rawDrawGhosts();
}

void GraphicGLManager::rawDrawGhostsEnabled(){
	for (int i = 0; i < opponents->getAmountOfOpponents(); i++) {
		if (opponents->getOpponentXmode(i) == Opponent::Mode::DISABLE) {
			Position opPos = opponents->getOpponentXposition(i);
			ghosts[i].draw(opPos);
		}
	}
}

void GraphicGLManager::rawDrawGhostsDisabled(){
	for (int i = 0; i < opponents->getAmountOfOpponents(); i++) {
		if (opponents->getOpponentXmode(i) == Opponent::Mode::DISABLE) {
			Position opPos = opponents->getOpponentXposition(i);
			disabledGhost.draw(opPos);
		}
	}
}

void GraphicGLManager::rawDrawGhosts(){
	for (int i = 0; i < opponents->getAmountOfOpponents(); i++) {
		Position opPos = opponents->getOpponentXposition(i);
		switch (opponents->getOpponentXmode(i)) {
		case Opponent::Mode::DEFEATED:
			defeatGhost.draw(opPos);
			break;
		case Opponent::Mode::ACTIVE:
			ghosts[i].draw(opPos);
			break;
		case Opponent::Mode::DISABLE:
			if (!isNearEnabledFlag) {
				disabledGhost.draw(opPos);
			}
		}
	}
}

void GraphicGLManager::drawHealth(){
	Position pos{2 , MapManager::instance().getMapYSize() };
	heartDrafter.setNumberOfLives(player->getAmountOfLifes());
	heartDrafter.draw(pos);
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
	case Event::DISABLE_ALL_OPPONENTS:
		isNearEnabledFlag = false;
		disabledFlag = true;
		break;
	case Event::ENABLE_ALL_OPPONENTS:
		isNearEnabledFlag = false;
		disabledFlag = false;
		break;
	case Event::WARNING_NEAR_ENABLE_ALL_OPPONENTS:
		isNearEnabledFlag = true;
		break;
	default:
		break;
	}
}
