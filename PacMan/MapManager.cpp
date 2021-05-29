#include "MapManager.h"

MapManager::MapManager(Board& map){
	std::move(map.begin(), map.end(), mapBoard.begin());
}

bool MapManager::isOccupied(Position& pos){
	auto foundIter = std::find(mapBoard.begin(), mapBoard.end(), pos);
	if (foundIter != mapBoard.end()) {
		return foundIter->isObstacle();
	}
	return false;
}
