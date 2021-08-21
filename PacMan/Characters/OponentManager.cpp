#include "OponentManager.h"


void OponentManager::createOponents(){
	CoordType opSpeed = CONFIG.getOponentSpeed();
	for (int i = 0; i < numberOfOponents; ++i) {
		ops.push_back({ getRandPosition(),
						std::make_shared<MoveAlg>(opSpeed) });
	}
}

void OponentManager::updateAll() {
	std::for_each(ops.begin(), ops.end(), [this](Oponent& op) { op.update(); });
}

void OponentManager::deactivateAll(){
	std::for_each(ops.begin(), ops.end(), [this](Oponent& op) { op.disable(); });
}

void OponentManager::activeteAll(){
	std::for_each(ops.begin(), ops.end(), [this](Oponent& op) { op.enable(); });
}

std::shared_ptr<Oponent> OponentManager::getOponent(int index){
	if (index >= 0 || index <= static_cast<int>(ops.size())) {
		return std::make_shared<Oponent>(ops[index]);
	}
	return nullptr;
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
		std::for_each(ops.begin(), ops.end(), [this](Oponent& op) { op.restoreInitialPosition(); });
		break;

	case Event::ALLOW_MOTION:
		std::for_each(ops.begin(), ops.end(), [this](Oponent& op) { op.unblockMotion(); });
		break;

	case Event::STOP_MOTION:
		std::for_each(ops.begin(), ops.end(), [this](Oponent& op) { op.stopMotion(); });
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