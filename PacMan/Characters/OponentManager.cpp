#include "OponentManager.h"


void OponentManager::createOponents(){
	char symbol = 'A';
	for (int i = 0; i < numberOfOponents; ++i) {
		ops.push_back({ getRandPosition(),
						 new Behaviour{new MoveAlg},
						  1,
						  {symbol} });
		symbol++;
	}
}


void OponentManager::updateAll() {
	for (auto& oponent : ops) {
		oponent.update();
	}
}

void OponentManager::drawAll() {
	for (auto& oponent : ops) {
		oponent.draw();
	}
}

void OponentManager::deactivateAll(){
	for (auto& oponent : ops) {
		oponent.disable();
	}
}

void OponentManager::activeteAll(){
	for (auto& oponent : ops) {
		oponent.enable();
	}
}

bool OponentManager::isOponentsAndDraw(Position& pos){
	auto pred = [&pos](const Oponent& oponent) {return oponent.getPosition() == pos; };
	auto oponentIter = find_if(ops.begin(), ops.end(), pred);
	if (oponentIter != ops.end()) {
		oponentIter->draw();
		return true;
	}
	return false;
}



Position OponentManager::getRandPosition() {
	while (true) {
		int randX = std::rand() % MapManager::instance().getMapXSize();
		int randY = std::rand() % MapManager::instance().getMapYSize();

		Position pos{ randX,randY };
		if (!MapManager::instance().isOccupied(pos)) {
			return pos;
		}
	}
	return Position{};
}
