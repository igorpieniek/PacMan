#pragma once
#include "Drafter.h"
#include "MapManager.h"
#include "Movement.h"
#include "MatrixTool.h"
#include "MapCreator.h"

#include <string>
#include <map>






class MapDrafter :public Drafter{
public:
	MapDrafter();
	void draw();

private:
	std::string turnPath     = "images/turn.png";
	std::string straightPath = "images/newMap.png";
	std::shared_ptr<Texture> cornerText;
	std::shared_ptr<Texture> straightText;
	Transformation mapTrans;

	std::map<Direction, float> rotations = {
		{Direction::EAST,    0.0f},
		{Direction::WEST,  180.0f},
		{Direction::NORTH,  90.0f},
		{Direction::SOUTH, -90.0f},
	};

	std::vector<MapCell> map;

	/*

	struct ObstacleInfo {
		Direction dir;
		MapPatternType type;
		Position pos;
		Transformation trans;
	};

	
	std::vector<ObstacleInfo> obstacles;
	PatternResult matchPattern(Position& cell);
	*/
};

