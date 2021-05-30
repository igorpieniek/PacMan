#pragma once

#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__


#include "MapCell.h"
#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include <algorithm>


using Board = std::vector<MapCell>;

class MapManager{
public:
	MapManager();
	MapManager(Board& map);

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

};


#endif //__MAPMANAGER_H__
