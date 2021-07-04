#include "DrawManager.h"

void DrawManager::addPlayer(const Player* pl){
	player = pl;
}

void DrawManager::addOponentManager(OponentManager* op){
	oponentManager = op;
	int index = 0;
	while (true) {
		Oponent* temp = oponentManager->getOponent(index);
		if (temp == nullptr) break;
		oponentDrafter[temp] = oponentDrafterFactor->getInstance();
	}
}

void DrawManager::drawAll(){

}
