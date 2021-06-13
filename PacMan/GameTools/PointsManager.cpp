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
