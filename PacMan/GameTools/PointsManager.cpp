#include "PointsManager.h"

/*
PointsManager::PointsManager(int specialAmount){
	// get map from mapmanager
	// calculate number of all posible
}
*/

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

void PointsManager::addPoints(Position& pos){
	auto iter = std::find(cellPoints.begin(), cellPoints.end(), pos);
	if (iter != cellPoints.end()) {
		currentPoints += iter->getPoints();
		cellPoints.erase(iter);
	}
}

void PointsManager::notify(Event evt){
}

void PointsManager::notifyPlayerPosition(Position& pos)
{
}
