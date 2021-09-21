#include "OpponentManager.h"
#include <time.h>


OpponentManager::OpponentManager(float speed, int numberOfOps) : opponentSpeed(speed), numberOfOpponents(numberOfOps) {
	createOpponents();
	Position potBase = CONFIG.getGhostBasePosition();
	if (!MapManager::instance().isOccupied(potBase)) {
		opponentBase = potBase;
	}
}

void OpponentManager::createOpponents(){
	ops.resize(numberOfOpponents);
	for (int i = 0; i < numberOfOpponents; ++i) {
		ops[i].setStartPosition(getRandPosition());
		ops[i].setMoveAlgorithm(std::make_unique<MoveAlgNormal>(opponentSpeed));
	}
}

void OpponentManager::updateAll() {
	for (auto& op : ops) {
		if (op.getPosition() == opponentBase
			&& op.getState() == Opponent::Mode::DEFEATED) {
			op.setMoveAlgorithm(std::make_unique<MoveAlgNormal>(opponentSpeed));
			op.setState(Opponent::Mode::ACTIVE);
		}
	}
	std::for_each(ops.begin(), ops.end(), [this](Opponent& op) { op.update(); });
}

void OpponentManager::deactivateAll(){
	for (auto& op : ops) {
		if (op.getState() == Opponent::Mode::ACTIVE) {
			op.setState(Opponent::Mode::DISABLE);
		}
	}
}

void OpponentManager::activeteAll(){
	for (auto& op : ops) {
		if (op.getState() == Opponent::Mode::DISABLE) {
			op.setState(Opponent::Mode::ACTIVE);
		}
	}
}

Position OpponentManager::getOpponentXposition(int index){
	if (index >= 0 || index <= static_cast<int>(ops.size())) {
		return ops[index].getPosition();
	}
	throw std::runtime_error("Bad opponent index!");
}

Opponent::Mode OpponentManager::getOpponentXmode(int index){
	if (index >= 0 || index <= static_cast<int>(ops.size())) {
		return ops[index].getState();
	}
	throw std::runtime_error("Bad opponent index!");
}

void OpponentManager::notify(Event evt){
	switch (evt){
	case Event::DISABLE_ALL_OPPONENTS:
		std::cout << "OpponentManager: DISABLE ALL\n";
		deactivateAll();
		break;

	case Event::ENABLE_ALL_OPPONENTS:
		std::cout << "OpponentManager: ENABLE ALL\n";
		activeteAll();
		break;

	case Event::RESTART_POSITIONS:
		restartAll();
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
	auto opIter = isPlayerPosReached(pos);
	if (opIter != ops.end()) {
		if (opIter->getState() == Opponent::Mode::ACTIVE) {
			mediator->notify(Event::PLAYER_CATCHED);
		}
		else if (opIter->getState() == Opponent::Mode::DISABLE) {
				mediator->notify(Event::DISABLED_GHOST_CATCHED);
				opIter->setMoveAlgorithm(std::make_unique<MoveAlgCatched>(opponentSpeed, opponentBase));
				opIter->setState(Opponent::Mode::DEFEATED);
		}
	}
}

std::vector<Opponent>::iterator OpponentManager::isPlayerPosReached(Position& pos){
	return std::find_if(ops.begin(), ops.end(),
		[&pos](const Opponent& op) {return op.getPosition().getIntPos() == pos.getIntPos(); });
}

void OpponentManager::restartAll(){
	for (auto& op : ops) {
		op.setState(Opponent::Mode::ACTIVE);
		op.restoreInitialPosition();
		op.setMoveAlgorithm(std::make_unique<MoveAlgNormal>(opponentSpeed));	
	}
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