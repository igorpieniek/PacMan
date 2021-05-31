#pragma once

#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__


#include "MapCell.h"
#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>


using Board = std::vector<MapCell>;

class MapManager{
public:
	MapManager();
	MapManager(Board& map);
	MapManager(std::string fileName);

	bool isOccupied(Position& pos);
	Board& getAllMap();
	Board getNeighbours(Position& pos, int radius);

	enum class Direction {
		NORTH,
		EAST,
		SOUTH,
		WEST
	};


	bool isCorner(Position& pos);
	std::vector<Direction> getAllPossibleDirections(Position& pos);
	
private:
	Board mapBoard;
	Board readMapFromFile(std::string fileName);

	const std::map<char, MapCell::Category> mapBindings = {
		{'1', MapCell::Category::OBSTACLE},
		{'0', MapCell::Category::FREE},
	};

};


#endif //__MAPMANAGER_H__
