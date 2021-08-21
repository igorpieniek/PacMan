#pragma once

#include "MapCell.h"
#include "Movement.h"
#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>
#include <cmath>


using Board = std::vector<MapCell>;


// Singleton class
class MapManager{
public:

	static MapManager& instance();

	void addMap(Board& map);
	void addMap(std::string filename);

	bool isOccupied(Position& pos);
	Board& getAllMap();
	Board getNeighbours(Position& pos, int radius);

	bool isCorner(Position& pos);
	std::vector<Direction> getAllPossibleDirections(Position& pos);

	CoordType getMapXSize() const { return static_cast<CoordType>(width); };
	CoordType getMapYSize() const { return static_cast<CoordType>(height); };
	int getFreePosAmount() const { return freePositionsAmount; };

	MapManager(MapManager const&) = delete;
	void operator=(MapManager const&) = delete;
	
private:
	MapManager() {};

	int width = 0, height = 0;

	Board mapBoard;
	Board readMapFromFile(std::string fileName);
	int freePositionsAmount = 0;
	void incrementFreePos(MapCell::Category cat);

	size_t getMapBoardIndexPosition(Position& pos);

	const std::map<char, MapCell::Category> mapBindings = {
		{'1', MapCell::Category::OBSTACLE},
		{'0', MapCell::Category::FREE},
	};

};
