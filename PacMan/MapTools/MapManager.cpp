#include "MapManager.h"


MapManager& MapManager::instance(){
	static MapManager inst;
	return inst;
}

void MapManager::addMap(Board& map){
	mapBoard = std::move(map);
}

void MapManager::addMap(std::string filename){
	mapBoard = readMapFromFile(filename);
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

	for (CoordType k = pos.getY() - radius; k <= pos.getY() + radius; ++k) {
		for (CoordType w = pos.getX() - radius; w <= pos.getX() + radius; ++w){
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
	std::vector<Direction> possible = getAllPossibleDirections(pos);
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

std::vector<Direction> 
MapManager::getAllPossibleDirections(Position& pos){
	std::vector<Direction> result;
	std::map<Direction, Position> check = {
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
	if (file.fail()) {
		std::cout << "Map file open error!" << std::endl;
	}
	std::string line;
	int lineNumber = 0;
	while ( std::getline(file, line)) {
		for ( int i = 0; i < (int)line.length(); i++) {
			auto it = mapBindings.find(line[i]);
			if (it != mapBindings.end()) {
				result.push_back({ { (CoordType)i, (CoordType)lineNumber}, it->second });
				incrementFreePos(it->second);
			}
		}
		++lineNumber;
	}
	return result;
}


void MapManager::incrementFreePos(MapCell::Category cat) {
	if (cat == MapCell::Category::FREE) {
		freePositionsAmount++;
	}
}
