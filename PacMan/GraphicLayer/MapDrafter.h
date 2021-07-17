#pragma once
#include "Drafter.h"
#include "MapManager.h"
#include "Movement.h"
#include <string>
#include <map>

class MapDrafter :public Drafter{
public:
	MapDrafter();
	void draw();

private:
	std::string turnPath     = "images/turn.png";
	std::string straightPath = "images/straight.png";

	std::map<Direction, float> rotations = {
		{Direction::EAST,    0.0f},
		{Direction::WEST,  180.0f},
		{Direction::NORTH,  90.0f},
		{Direction::SOUTH, -90.0f},
	};

	std::vector<MapCell> map;


	struct ObstacleInfo {
		Direction dir;
		Position pos;
	};

	
	std::vector<ObstacleInfo> obstacles;

};

