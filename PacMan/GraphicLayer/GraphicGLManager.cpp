#include "GraphicGLManager.h"

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

