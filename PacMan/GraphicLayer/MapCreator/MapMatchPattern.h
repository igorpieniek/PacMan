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
	std::vector<MapPatternType> getMatchForWholeMap();

private:
	enum class Rotation {
		DEG0, DEG90, DEG180, DEG270
	};


	std::vector<Rotation>  rotations = { Rotation::DEG0,
										 Rotation::DEG90, 
										 Rotation::DEG180, 
										 Rotation::DEG270 };
	MatrixTool<int> matTool;

	MapPatternType matchPatternForCell(Position& cell);
	int getNumberOfHitsForPattern(const Board& square, const MapPatternData& pat);
	MapPatternType getProperType(const MapPatternType type, const Rotation rot);
	MapPatternType getNextTypeClockWise(const MapPatternType);


};

