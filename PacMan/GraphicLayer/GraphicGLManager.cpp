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

	//mapDrafter.addImage(mapPath);
	plDrafter.addImage(playerPath);
	cookieDrafter.addImage(cookiePath);

	mapDrafter.addImage(mapPath);

	
	// initialize PlayerDrafter object
	// initialize GhostDrafter objects:
	//		add to map  like 'oponentsWithDrafter' <Oponent*, GhostDrafter>


}

void GraphicGLManager::draw(){
	//drawObstacles();
	mapDrafter.draw();

	for (const auto& cookie : points->getPointsData()) {
		if (cookie.getPointClass() == PointCat::SPECIAL) {
			cookieDrafter.setSpecialPoint();
		}
		cookieDrafter.draw(cookie, Direction::EAST);
	}

	plDrafter.updateIsMoving(player->isMoving());
	plDrafter.draw(player->getPosition(), player->getCurrentDirection());
	

	for (int i = 0; i < oponents->getAmountOfOponents(); i++) {
		std::shared_ptr<Oponent> opPos = oponents->getOponent(i);
		ghosts[i].draw(opPos->getPosition(), Direction::EAST);
	}

	Render2D::instance().process();
}




std::string GraphicGLManager::getnextGhostPath(){
	static int counter;
	if (counter >= ghostPaths.size()) {
		counter = 0;
	}
	return ghostPaths[counter++];
}


void GraphicGLManager::notify(Event evt) {
	switch (evt)
	{
	case Event::SPECIAL_POINT_REACHED:
		break;
	case Event::ALL_POINTS_COLLECTED:
		break;
	case Event::DISABLE_ALL_OPONENTS:
		break;
	case Event::ENABLE_ALL_OPONENTS:
		break;
	case Event::PLAYER_CATCHED:
		break;
	case Event::END_OF_LIVES:
		break;
	case Event::LIFE_LOST:
		break;
	case Event::RESTART_POSITIONS:
		break;
	case Event::ALLOW_MOTION:
		break;
	case Event::STOP_MOTION:
		break;
	default:
		break;
	}
}
