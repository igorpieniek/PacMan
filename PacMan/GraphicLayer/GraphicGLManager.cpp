#include "GraphicGLManager.h"

GraphicGLManager::GraphicGLManager(const std::shared_ptr<Player> pl,
	std::shared_ptr<OponentManager> oponentManag)
	: GraphicManagerInterface(pl, oponentManag)
{

	calculateScale();
	Render2D::instance().init();

	for (int i = 0; i < oponents->getAmountOfOponents(); i++) {
		ghosts.push_back({});
		ghosts.back().addImage(getnextGhostPath());
	}


	mapDrafter.addImage("images/dot.png");
	mapvec = MapManager::instance().getAllMap();
	// initialize PlayerDrafter object
	// initialize GhostDrafter objects:
	//		add to map  like 'oponentsWithDrafter' <Oponent*, GhostDrafter>


}

void GraphicGLManager::draw(){
	drawObstacles();
	for (int i = 0; i < oponents->getAmountOfOponents(); i++) {
		std::shared_ptr<Oponent> opPos = oponents->getOponent(i);
		Position pos = opPos->getPosition();

		pos = Position{ getNormalized(pos.getX()), 
					    getNormalized(pos.getY()) };

		ghosts[i].draw(pos, Direction::EAST);
	}

	Render2D::instance().process();

}



void GraphicGLManager::calculateScale() {
	CoordType max = std::max(MapManager::instance().getMapXSize(),
						     MapManager::instance().getMapYSize());
	scale = 2 / max;
}

CoordType GraphicGLManager::getNormalized(CoordType cord){
	return (cord * scale) - 1.0f;
}

void GraphicGLManager::drawObstacles(){
	for (auto& cell : mapvec) {
		if (cell.isObstacle()) {
			mapDrafter.draw(Position{ getNormalized(cell.getX()), getNormalized(cell.getY()) }, Direction::EAST);
		}
	}
}

std::string GraphicGLManager::getnextGhostPath(){
	static int counter;
	if (counter >= ghostPaths.size()) {
		counter = 0;
	}
	return ghostPaths[counter++];
}

