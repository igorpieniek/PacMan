#pragma once
#include "Drafter.h"
#include "MapManager.h"
#include "Movement.h"
#include "MatrixTool.h"
#include <string>
#include <map>


enum class MapPatternType {
	STRAIGHT, CORNER
};


struct MapPatternData {
	MapPatternType type;
	std::vector<int> arr;
};

struct PatternResult {
	Direction dir;
	MapPatternType cat;
	bool isFound;
};



class MapDrafter :public Drafter{
public:
	MapDrafter();
	void draw();

private:
	std::string turnPath     = "images/turn.png";
	std::string straightPath = "images/straight.png";
	std::shared_ptr<Texture> cornerText;
	std::shared_ptr<Texture> straightText;

	std::map<Direction, float> rotations = {
		{Direction::EAST,    0.0f},
		{Direction::WEST,  180.0f},
		{Direction::NORTH,  90.0f},
		{Direction::SOUTH, -90.0f},
	};

	std::vector<MapCell> map;



	struct ObstacleInfo {
		Direction dir;
		MapPatternType type;
		Position pos;
	};

	
	std::vector<ObstacleInfo> obstacles;
	PatternResult matchPattern(Position& cell);

};

