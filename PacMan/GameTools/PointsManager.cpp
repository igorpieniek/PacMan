#include "PointsManager.h"



void PointsManager::createCellPointArray(){
	int counter = 0;
	int divider = (int)(MapManager::instance().getFreePosAmount() / specialPointsAmount);
	for (auto const& cell : MapManager::instance().getAllMap()) {
		if (!cell.isObstacle()) {
			counter++;
			Position pos = static_cast<Position>(cell);
			if (counter % divider == 0) {
				cellPoints.push_back({ pos, PointCat::SPECIAL });
			}
			else {
				cellPoints.push_back({ pos, PointCat::NORMAL });
			}
		}
	}
}

void PointsManager::notifyPlayerPosition(Position& pos) {
	if (isAllPointsReached()) {
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
		currentPoints = 0;
		cellPoints.clear();
		createCellPointArray();
	}
}





