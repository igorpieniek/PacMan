#include "PointsManager.h"

void PointsManager::createCellPointArray(){
	int counter = 0;
	if (MapManager::instance().getFreePosAmount() < specialPointsAmount) {
		std::cout<< "PointsManager: there cannot be more special points than amout of free positions!" << std::endl;
		specialPointsAmount = MapManager::instance().getFreePosAmount();
	}

	int divider = (int)(MapManager::instance().getFreePosAmount() / specialPointsAmount);
	Position playerInitPos = CONFIG.getPlayerInitialPosition();
	for (auto const& cell : MapManager::instance().getAllMap()) {
		if (!cell.isObstacle()) {
			counter++;
			Position pos = static_cast<Position>(cell);
			if (counter % divider == 0 && pos != playerInitPos) {
				cellPoints.push_back({ pos, PointCat::SPECIAL });
			}
			else {
				cellPoints.push_back({ pos, PointCat::NORMAL });
			}
		}
	}
}

void PointsManager::notifyPlayerPosition(Position& pos) {
	if (isAllPointsReached() && !lockPlayerPosNotify) {
		lockPlayerPosNotify = true;
		mediator->notify(Event::ALL_POINTS_COLLECTED);
		return;
	}

	auto it = getCellPointIter(pos);
	if (it != cellPoints.end()) {
		addPoints(it);
		checkSpecialPoint(it);
		removeCellPoint(it);
	}
}

bool PointsManager::isAllPointsReached()const {
	return cellPoints.empty();
}

PointsManager::CellPointIter PointsManager::getCellPointIter(Position& pos) {
	return std::find(cellPoints.begin(), cellPoints.end(), pos.getIntPos());
}

void  PointsManager::addPoints(CellPointIter& it) {	
	if (!firstPointVal) {
		firstPointVal = it->getPoints();
		currentPoints = -firstPointVal;
	}
	currentPoints += it->getPoints();
}

void PointsManager::checkSpecialPoint(CellPointIter& it) {
	if (it->getPointClass() == PointCat::SPECIAL) {
		mediator->notify(Event::SPECIAL_POINT_REACHED);
	}
}

void PointsManager::removeCellPoint(CellPointIter& it){
	cellPoints.erase(it);
}

void PointsManager::notify(Event evt){
	if (evt == Event::RESET_GAME) {	
		currentPoints = -firstPointVal;
		cellPoints.clear();
		createCellPointArray();
		lockPlayerPosNotify = false;
	}
}





