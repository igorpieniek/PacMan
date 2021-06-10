#include "OponentManager.h"

void OponentManager::createOponents(){

	for (int i = 0; i < numberOfOponents; ++i) {
		MoveAlg alg{};
		Behaviour beh{ &alg };
		algbeh.push_back({ alg, beh });
	}

	for (int i = 0; i < numberOfOponents; ++i) {
		ops.push_back({ Position{0,0},
						 &algbeh[i].beh,
						  1,
						  "G" });
	}
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
