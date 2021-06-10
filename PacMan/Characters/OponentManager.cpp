#include "OponentManager.h"


void OponentManager::createOponents(){

	for (int i = 0; i < numberOfOponents; ++i) {
		MoveAlg alg{};
		Behaviour beh{ &alg };
		algbeh.push_back({ alg, beh });
	}

	for (int i = 0; i < numberOfOponents; ++i) {
		ops.push_back({ getRandPosition(),
						 &algbeh[i].beh,
						  1,
						  "G" });
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
	Position pos{ 0,0 };
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
