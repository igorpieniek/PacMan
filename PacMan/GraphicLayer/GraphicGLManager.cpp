#include "GraphicGLManager.h"

GraphicGLManager::GraphicGLManager(const std::shared_ptr<Player> pl, 
								   const std::shared_ptr<OponentManager> oponentManag)
	: GraphicManagerInterface(pl,oponentManag)
{
	Render2D::instance().init();
	ghost1.addImage("images/ghost.png");
	// initialize PlayerDrafter object
	// initialize GhostDrafter objects:
	//		add to map  like 'oponentsWithDrafter' <Oponent*, GhostDrafter>


}

void GraphicGLManager::draw(){
	std::shared_ptr<Oponent> opPos = oponents->getOponent(0);
	Position pos = opPos->getPosition();

	ghost1.draw(pos / 30.0f, Direction::EAST);

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
