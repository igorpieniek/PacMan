#pragma once

#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__


#include "MapCell.h"
#include <vector>
#include <utility>
#include <iostream>


using Board = std::vector<MapCell>;

class MapManager{
public:
	MapManager();
	MapManager(Board& map);

	bool isOccupied(Position& pos);
	//Board& getAllMap();
	//Board getNeighbour(Position& pos, int radius);
	
private:
	Board mapBoard;
};


#endif //__MAPMANAGER_H__
