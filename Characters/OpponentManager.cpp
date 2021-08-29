#include "OpponentManager.h"
#include <time.h>


OpponentManager::OpponentManager(float speed, int numberOfOps) : opponentSpeed(speed), numberOfOpponents(numberOfOps) {
	std::srand((unsigned)time(NULL));
	createOpponents();
}

void OpponentManager::createOpponents(){
	for (int i = 0; i < numberOfOpponents; ++i) {
		ops.push_back({ getRandPosition(),
						std::make_shared<MoveAlg>(opponentSpeed) });
	}
}

void OpponentManager::updateAll() {
	std::for_each(ops.begin(), ops.end(), [this](Opponent& op) { op.update(); });
}

void OpponentManager::deactivateAll(){
	std::for_each(ops.begin(), ops.end(), [this](Opponent& op) { op.disable(); });
}

void OpponentManager::activeteAll(){
	std::for_each(ops.begin(), ops.end(), [this](Opponent& op) { op.enable(); });
}

std::shared_ptr<Opponent> OpponentManager::getOpponent(int index){
	if (index >= 0 || index <= static_cast<int>(ops.size())) {
		return std::make_shared<Opponent>(ops[index]);
	}
	return nullptr;
}

void OpponentManager::notify(Event evt){
	switch (evt){
	case Event::DISABLE_ALL_OPPONENTS:
		std::cout << "OpponentManager: DISABLE ALL\n";
		deactivateAll();
		active = false;
		break;

	case Event::ENABLE_ALL_OPPONENTS:
		std::cout << "OpponentManager: ENABLE ALL\n";
		activeteAll();
		active = true;
		break;

	case Event::RESTART_POSITIONS:
		std::for_each(ops.begin(), ops.end(), [this](Opponent& op) { op.restoreInitialPosition(); });
		break;

	case Event::ALLOW_MOTION:
		std::for_each(ops.begin(), ops.end(), [this](Opponent& op) { op.unblockMotion(); });
		break;

	case Event::STOP_MOTION:
		std::for_each(ops.begin(), ops.end(), [this](Opponent& op) { op.stopMotion(); });
		break;
	}
}

void OpponentManager::notifyPlayerPosition(Position& pos){
	if (active && isPlayerPosReached(pos)) {
		mediator->notify(Event::PLAYER_CATCHED);
	}
}

bool OpponentManager::isPlayerPosReached(Position& pos){
	for (const auto& op : ops) {
		if (op.getPosition().getIntPos() == pos.getIntPos()) return true;
	}
	return false;
}

Position OpponentManager::getRandPosition() {
	while (true) {
		int randX = std::rand() % static_cast<int>( MapManager::instance().getMapXSize() );
		int randY = std::rand() % static_cast<int>( MapManager::instance().getMapYSize() );

		Position pos{ static_cast<CoordType>(randX),
				      static_cast<CoordType>(randY) };
		if (!MapManager::instance().isOccupied(pos) &&
			pos.getIntPos() != CONFIG.getPlayerInitialPosition().getIntPos()) {
			return pos;
		}
	}
	return Position{};
}