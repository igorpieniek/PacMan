#include "Opponent.h"

void Opponent::update(){
	if (isMotionBlocked) return;
	if (behaviour) {
		behaviour->update(currentPostion);
	}
	else {
		throw std::runtime_error("Opponent: No behaviour algorithm added!");
	}
}

void Opponent::setStartPosition(Position&& pos) {
	initPositionSnapshot = pos;
	currentPostion = pos;
}

void Opponent::setMoveAlgorithm(std::unique_ptr<MoveAlgorithm>&& beh) {
	behaviour = std::move(beh);
}



