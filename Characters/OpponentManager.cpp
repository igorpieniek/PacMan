#include "OpponentManager.h"
#include <time.h>


OpponentManager::OpponentManager(float speed, int numberOfOps) : opponentSpeed(speed), numberOfOpponents(numberOfOps) {
	createOpponents();
}

void OpponentManager::createOpponents(){
	ops.resize(numberOfOpponents);
	for (int i = 0; i < numberOfOpponents; ++i) {
		ops[i].setStartPosition(getRandPosition());
		ops[i].setMoveAlgorithm(std::make_unique<MoveAlg>(opponentSpeed));
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

Position OpponentManager::getOpponentXposition(int index){
	if (index >= 0 || index <= static_cast<int>(ops.size())) {
		return ops[index].getPosition();
	}
	return Position{};
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
	static bool catchOnce = true;
	if (isPlayerPosReached(pos)) {
		if (active) {
			mediator->notify(Event::PLAYER_CATCHED);
		}
		else if(catchOnce){
			mediator->notify(Event::DISABLED_GHOST_CATCHED);
			catchOnce = false;
		}
	}
	else {
		catchOnce = true;
	}
}

bool OpponentManager::isPlayerPosReached(Position& pos){
	for (const auto& op : ops) {
		if (op.getPosition().getIntPos() == pos.getIntPos()) return true;
	}
	return false;
}

Position OpponentManager::getRandPosition() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randomizerX(0, static_cast<int>(MapManager::instance().getMapXSize()) );
	std::uniform_int_distribution<> randomizerY(0, static_cast<int>(MapManager::instance().getMapYSize()) );
	while (true) {
		int randX = randomizerX(gen);
		int randY = randomizerY(gen);

		Position pos{ static_cast<CoordType>(randX),
				      static_cast<CoordType>(randY) };
		if (!MapManager::instance().isOccupied(pos) &&
			pos.getIntPos() != CONFIG.getPlayerInitialPosition().getIntPos()) {
			return pos;
		}
	}
	return Position{};
}