#include "OpponentManager.h"
#include <time.h>


OpponentManager::OpponentManager(float speed, int numberOfOps) : opponentSpeed(speed), numberOfOpponents(numberOfOps) {
	createOpponents();
	Position potBase = CONFIG.getGhostBasePosition();
	if (!MapManager::instance().isOccupied(potBase)) {
		opponentBase = potBase;
	}
	additionalDisableTimer.setCallback(std::bind(&OpponentManager::nearEnableAllCb, this));
	mainDisableTimer.setCallback(std::bind(&OpponentManager::enableAllTimerCb, this));
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
			op.setMoveAlgorithm(std::make_unique<MoveAlgNormal>(opponentSpeed*0.5f));
		}
	}
}

void OpponentManager::activeteAll(){
	for (auto& op : ops) {
		if (op.getState() == Opponent::Mode::DISABLE) {
			op.setState(Opponent::Mode::ACTIVE);
			op.setMoveAlgorithm(std::make_unique<MoveAlgNormal>(opponentSpeed));
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
		setGhostDisableTimer();
		break;

	case Event::ENABLE_ALL_OPPONENTS:
		std::cout << "OpponentManager: ENABLE ALL\n";
		activeteAll();
		break;

	case Event::RESTART_POSITIONS:
		restartAll();
		break;

	case Event::RESET_OPPONENTS_STATE:
		additionalDisableTimer.reset();
		mainDisableTimer.reset();
		currentGhostDisableTime = 0;
		break;

	case Event::ALLOW_MOTION:
		std::for_each(ops.begin(), ops.end(), [this](Opponent& op) { op.unblockMotion(); });
		break;

	case Event::STOP_MOTION:
		std::for_each(ops.begin(), ops.end(), [this](Opponent& op) { op.stopMotion(); });
		break;
	}
}

void OpponentManager::notifyPlayerPosition(const Position& pos){
	auto opIter = isPlayerPosReached(pos);
	if (opIter != ops.end()) {
		if (opIter->getState() == Opponent::Mode::ACTIVE) {
			mediator->notify(Event::PLAYER_CATCHED);
		}
		else if (opIter->getState() == Opponent::Mode::DISABLE) {
				mediator->notify(Event::DISABLED_GHOST_CATCHED);
				opIter->setMoveAlgorithm(std::make_unique<MoveAlgCatched>(opponentSpeed*2, opponentBase));
				opIter->setState(Opponent::Mode::DEFEATED);
		}
	}
}

std::vector<Opponent>::iterator OpponentManager::isPlayerPosReached(const Position& pos){
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
			CONFIG.getPlayerInitialPosition().distance(pos) > 3.0f ) {
			return pos;
		}
	}
	return Position{};
}

void OpponentManager::setGhostDisableTimer() {
	if (currentGhostDisableTime == 0) {
		additionalDisableTimer.startPeriodElapse(normalDisableTime);
	}
	currentGhostDisableTime += normalDisableTime;
}

void OpponentManager::nearEnableAllCb() {
	currentGhostDisableTime -= normalDisableTime;
	std::cout << "Current disable time " << currentGhostDisableTime << std::endl;
	if (currentGhostDisableTime == 0) {
		mediator->notify(Event::WARNING_NEAR_ENABLE_ALL_OPPONENTS);
		mainDisableTimer.startPeriodElapse(warningDisableTime);
	}
	else {
		deactivateAll();
		additionalDisableTimer.startPeriodElapse(normalDisableTime);
	}
}

void OpponentManager::enableAllTimerCb() {
	if (currentGhostDisableTime == 0) {
		activeteAll();
	}
}