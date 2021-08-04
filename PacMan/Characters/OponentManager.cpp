#include "OponentManager.h"


void OponentManager::createOponents(){
	CoordType opSpeed = CONFIG.getOponentSpeed();
	for (int i = 0; i < numberOfOponents; ++i) {
		ops.push_back({ getRandPosition(),
						std::make_shared<MoveAlg>(opSpeed) });
	}
}

void OponentManager::updateAll() {
	for (auto& oponent : ops) {
		oponent.update();
	}
}

void OponentManager::drawAll() {
	for (auto& oponent : ops) {
		//oponent.draw();
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

std::shared_ptr<Oponent> OponentManager::getOponent(int index){
	if (index >= 0 || index <= ops.size()) {
		return std::make_shared<Oponent>(ops[index]);
	}
	return nullptr;
}

bool OponentManager::isOponentsAndDraw(Position& pos){
	auto pred = [&pos](const Oponent& oponent) {return oponent.getPosition() == pos; };
	auto oponentIter = find_if(ops.begin(), ops.end(), pred);
	if (oponentIter != ops.end()) {
		//oponentIter->draw();
		return true;
	}
	return false;
}

void OponentManager::notify(Event evt){
	switch (evt){
	case Event::DISABLE_ALL_OPONENTS:
		std::cout << "OponentManager: DISABLE ALL\n";
		deactivateAll();
		active = false;
		break;
	case Event::ENABLE_ALL_OPONENTS:
		std::cout << "OponentManager: ENABLE ALL\n";
		activeteAll();
		active = true;
		break;
	case Event::RESTART_POSITIONS:
		for (auto& oponent : ops) {
			oponent.restoreInitialPosition();
		}
		break;
	case Event::ALLOW_MOTION:
		for (auto& oponent : ops) {
			oponent.unblockMotion();
		}
		break;
	case Event::STOP_MOTION:
		for (auto& oponent : ops) {
			oponent.stopMotion();
		}
		break;
	}
}

void OponentManager::notifyPlayerPosition(Position& pos){
	if (active && isPlayerPosReached(pos)) {
		mediator->notify(Event::PLAYER_CATCHED);
	}
}

bool OponentManager::isPlayerPosReached(Position& pos){
	for (const auto& op : ops) {
		if (op.getPosition().getIntPos() == pos.getIntPos()) return true;
	}
	return false;
}

Position OponentManager::getRandPosition() {
	while (true) {
		int randX = std::rand() % static_cast<int>( MapManager::instance().getMapXSize() );
		int randY = std::rand() % static_cast<int>( MapManager::instance().getMapYSize() );

		Position pos{ static_cast<CoordType>(randX),
				      static_cast<CoordType>(randY) };
		if (!MapManager::instance().isOccupied(pos)) {
			return pos;
		}
	}
	return Position{};
}