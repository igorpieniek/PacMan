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

Board& MapManager::getAllMap(){
	return mapBoard;
}

Board MapManager::getNeighbours(Position& pos, int radius){
	Board resultMap;

	for (int w = pos.getX() + radius; w <= pos.getX() + radius; w++) {
		for (int k = pos.getY() + radius; k <= pos.getY() + radius; k++) {
			Board::iterator iter = std::find(mapBoard.begin(), mapBoard.end(), Position{ w,k });
			if (iter != mapBoard.end()) {
				resultMap.push_back(*iter);
			}
			else {
				resultMap.push_back(MapCell{ Position{w,k}, MapCell::Category::OBSTACLE });
			}
		}
	}

	return resultMap;
}

bool MapManager::isCorner(){
	return false;
}

std::vector<MapManager::Direction> 
MapManager::getAllPossibleDirections(Position& pos){
	return std::vector<MapManager::Direction>();
}
