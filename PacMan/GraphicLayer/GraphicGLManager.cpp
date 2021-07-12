#include "GraphicGLManager.h"

GraphicGLManager::GraphicGLManager(const std::shared_ptr<Player> pl,
	std::shared_ptr<OponentManager> oponentManag)
	: GraphicManagerInterface(pl, oponentManag)
{
	Render2D::instance().init();
	for (int i = 0; i < 4; i++) {
		ghosts.push_back({});
	}
	ghosts[0].addImage("images/ghost1.png");
	ghosts[1].addImage("images/ghost2.png");
	ghosts[2].addImage("images/ghost3.png");
	ghosts[3].addImage("images/ghost4.png");
	// initialize PlayerDrafter object
	// initialize GhostDrafter objects:
	//		add to map  like 'oponentsWithDrafter' <Oponent*, GhostDrafter>


}

void GraphicGLManager::draw(){
	for (int i = 0; i < 4; i++) {
		std::shared_ptr<Oponent> opPos = oponents->getOponent(i);
		Position pos = opPos->getPosition();
		pos = pos / 15;
		pos = Position{ pos.getX() - 1.f, pos.getY() - 0.5f };

		ghosts[i].draw(pos, Direction::EAST);
	}

	Render2D::instance().process();
	/*
	
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
