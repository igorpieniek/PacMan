#include "DrawManager.h"

void DrawManager::addPlayer(std::shared_ptr<Player> pl){
	player = pl;
}

void DrawManager::addOponentManager(std::shared_ptr<OponentManager> op){
	oponentManager = op;
	int index = 0;
	while (true) {
		std::shared_ptr<Oponent> temp = oponentManager->getOponent(index);
		if (temp == nullptr) break;
		oponentDrafter[temp] = oponentDrafterFactor->getInstance();
	}
}

void DrawManager::drawAll(){

}
