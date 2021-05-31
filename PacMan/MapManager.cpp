#include "MapManager.h"

MapManager::MapManager(Board& map){
	mapBoard = std::move(map);
}

MapManager::MapManager(std::string fileName){
	mapBoard = readMapFromFile(fileName);
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

	for (int k = pos.getY() - radius; k <= pos.getY() + radius; k++) {
		for (int w = pos.getX() - radius; w <= pos.getX() + radius; w++){
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

bool MapManager::isCorner(Position& pos){
	std::vector<MapManager::Direction> possible = getAllPossibleDirections(pos);
	if (possible.size() != 2) return false;
	
	std::sort(possible.begin(), possible.end());
	//check next elements
	for (auto it = possible.begin(); it != possible.end()-1; it++) {
		int current = static_cast<int>(*it);
		int next = static_cast<int>(*(it+1));
		if ((next - current) == 1) return true;
	}
	//check last and first
	int front = static_cast<int>(possible.front());
	int back =  static_cast<int>(possible.back());
	if ((back - front) == 1) return true;

	return false;
}

std::vector<MapManager::Direction> 
MapManager::getAllPossibleDirections(Position& pos){
	std::vector<MapManager::Direction> result;
	std::map<MapManager::Direction, Position> check = {
		{Direction::NORTH, {0, 1}},
		{Direction::SOUTH, {0,-1}},
		{Direction::EAST,  {1, 0}},
		{Direction::WEST,  {-1,0}},
	};

	for (auto const& x : check) {
		Board::iterator iter = std::find(mapBoard.begin(),
										 mapBoard.end(),
										 pos + x.second);
		if (iter != mapBoard.end()) {
			if (!iter->isObstacle()) result.push_back(x.first);
		}
	}
	return result;
}

Board MapManager::readMapFromFile(std::string fileName){
	std::vector<MapCell> result;
	std::ifstream file(fileName);
	std::string line;
	int lineNumber = 0;
	while ( std::getline(file, line)) {
		for (auto i = 0; i < line.size(); i++) {
			auto it = mapBindings.find(line[i]);
			if (it != mapBindings.end()) {
				result.push_back({ {lineNumber,i}, it->second });
			}
		}
		++lineNumber;
	}
	return result;
}


