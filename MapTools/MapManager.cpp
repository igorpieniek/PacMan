#include "MapManager.h"
#include <string>


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
	if (pos.getX() >= width  || pos.getX() < 0) return true;
	if (pos.getY() >= height || pos.getY() < 0) return true;

	size_t cellIndex = getMapBoardIndexPosition(pos);

	if (cellIndex >= mapBoard.size()) return true;

	return mapBoard[cellIndex].isObstacle();
}

Board& MapManager::getAllMap(){
	return mapBoard;
}

Board MapManager::getNeighbours(Position& pos, int radius){
	Board resultMap;
	resultMap.reserve(std::pow((2 * radius + 1), 2));

	for (CoordType k = pos.getY() - radius; k <= pos.getY() + radius; ++k) {
		for (CoordType w = pos.getX() - radius; w <= pos.getX() + radius; ++w){
			Position searchPos = { w,k };
			size_t cellIndex = getMapBoardIndexPosition(searchPos);
			if (cellIndex < mapBoard.size()) {
				resultMap.push_back(mapBoard[cellIndex]);
			}
			else {
				resultMap.push_back(MapCell{ Position{w,k}, MapCell::Category::OBSTACLE });
			}
		}
	}

	return std::move(resultMap);
}

/*
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
*/


Board MapManager::readMapFromFile(std::string fileName){
	Board result;
	std::ifstream file(fileName);
	if (file.fail()) {
		throw std::runtime_error("Map file open error!");
	}
	std::string line;
	int lineNumber = 0;
	while ( std::getline(file, line)) {
		updateMapWidth(line.length());
		for ( int i = 0; i < (int)line.length(); i++) {
			auto it = mapBindings.find(line[i]);
			if (it != mapBindings.end()) {
				result.push_back({ { (CoordType)i, (CoordType)lineNumber}, it->second });
				incrementFreePos(it->second);
			}
			else {
				throw std::runtime_error("MapManager: Unknown sign in map txt file: " + std::string(1,line[i]));
			}
		}
		++lineNumber;
	}

	height = lineNumber;
	return std::move(result);
}

void MapManager::updateMapWidth(int w){
	if (width == 0) {
		width = w;
		return;
	}

	if (w != width) throw std::runtime_error("MapManager: Different width of lines in map txt file!");
	width = w;
}


void MapManager::incrementFreePos(MapCell::Category cat) {
	if (cat == MapCell::Category::FREE) {
		freePositionsAmount++;
	}
}

size_t MapManager::getMapBoardIndexPosition(Position& pos){
	Position conv = pos.getIntPos();
	return  static_cast<size_t>( (conv.getY() * width) + conv.getX() );
}
