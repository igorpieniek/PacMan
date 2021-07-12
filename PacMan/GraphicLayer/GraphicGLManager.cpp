#include "GraphicGLManager.h"

GraphicGLManager::GraphicGLManager(const std::shared_ptr<Player> pl, 
								   const std::shared_ptr<OponentManager> oponentManag)
	: GraphicManagerInterface(pl,oponentManag)
{
	// initialize PlayerDrafter object
	// initialize GhostDrafter objects:
	//		add to map  like 'oponentsWithDrafter' <Oponent*, GhostDrafter>


}

void GraphicGLManager::draw(){
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
