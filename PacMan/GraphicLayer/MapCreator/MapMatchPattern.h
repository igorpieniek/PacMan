#pragma once

#include <vector>
#include "Movement.h"
#include "MapManager.h"
#include "MatrixTool.h"

enum class MapPatternType {
	FREE,
	VERTICAL,
	HORIZONTAL,
	CORNER_CONVEX_NE,
	CORNER_CONVEX_SE,
	CORNER_CONVEX_SW,
	CORNER_CONVEX_NW,
	CORNER_CONCAVE_NE,
	CORNER_CONCAVE_SE,
	CORNER_CONCAVE_SW,
	CORNER_CONCAVE_NW,
};



struct MapPatternData {
	MapPatternType type;
	std::vector<int> arr;
};


class MapMatchPattern{
public:

private:
	enum class Rotation {
		DEG0, DEG90, DEG180, DEG270
	};
	struct ObstacleInfo {
		Direction dir;
		MapPatternType type;
		Position pos;
	};


	std::vector<ObstacleInfo> obstacles;
	MapPatternType matchPatternForCell(Position& cell);
	MapPatternType getProperType(const MapPatternType type, const Rotation rot);
	MapPatternType getNextTypeClockWise(const MapPatternType);


};

