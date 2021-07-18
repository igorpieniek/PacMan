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
	std::shared_ptr<Texture> cornerText;
	std::shared_ptr<Texture> straightText;

	std::map<Direction, float> rotations = {
		{Direction::EAST,    0.0f},
		{Direction::WEST,  180.0f},
		{Direction::NORTH,  90.0f},
		{Direction::SOUTH, -90.0f},
	};

	std::vector<MapCell> map;


	enum class ObstacleType {
		STRAIGHT, CORNER
	};
	struct ObstacleInfo {
		Direction dir;
		ObstacleType type;
		Position pos;
	};

	
	std::vector<ObstacleInfo> obstacles;

	bool isStraight(Direction& result, std::vector<bool>& status);
	bool isCorner(Direction& result, std::vector<bool>& status);

};

