#include "GraphicGLManager.h"

GraphicGLManager::GraphicGLManager(const std::shared_ptr<Player> pl,
	std::shared_ptr<OponentManager> oponentManag)
	: GraphicManagerInterface(pl, oponentManag)
{

	calculateScale();
	Render2D::instance().init();

	for (int i = 0; i < 4; i++) {
		ghosts.push_back({});
	}
	ghosts[0].addImage("images/ghost1.png");
	ghosts[1].addImage("images/ghost2.png");
	ghosts[2].addImage("images/ghost3.png");
	ghosts[3].addImage("images/ghost4.png");

	mapDrafter.addImage("images/dot.png");
	mapvec = MapManager::instance().getAllMap();
	// initialize PlayerDrafter object
	// initialize GhostDrafter objects:
	//		add to map  like 'oponentsWithDrafter' <Oponent*, GhostDrafter>


}

void GraphicGLManager::draw(){
	drawObstacles();
	for (int i = 0; i < 4; i++) {
		std::shared_ptr<Oponent> opPos = oponents->getOponent(i);
		Position pos = opPos->getPosition();

		pos = Position{ getNormalized(pos.getX()), 
					    getNormalized(pos.getY()) };

		ghosts[i].draw(pos, Direction::EAST);
	}

	Render2D::instance().process();
	/*
		//IDEAS
		???draw map????

		Position pos = player->getPosition();
		Direction dir = player->getDirection();
		playerDrafter.draw(pos,dir);
	
		for(auto& op : oponnnetWithDrafter){
			Position pos = op.first->getPosition();
			Direction dir = op.first->getDirection();
			//remember to remap position - different coordinates limits!!

			op.second.draw(pos,dir);

		}
	*/
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
