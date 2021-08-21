#include "MapMatchPattern.h"

//TODO: move to some.config file
// 0 - means position free
// 1 - means obstacle
// 2 - means that it doesn't matter
static const std::vector<MapPatternData> patterns = {
	{
		MapPatternType::VERTICAL,
		{1,1,2,
		 1,1,0,
		 1,1,2}
		},
	{
		MapPatternType::CORNER_CONVEX_NW, 
		{0,0,2,
		 0,1,1,
		 2,1,1}
		},
	{
		MapPatternType::CORNER_CONCAVE_SE,
		{1,1,1,
		 1,1,1,
		 1,1,0}
	}
};

std::vector<MapPatternType> MapMatchPattern::getMatchForWholeMap(){
	std::vector<MapPatternType> result;
	for (auto& cell : MapManager::instance().getAllMap()) {
		if (cell.isObstacle()) {
			result.push_back(matchPatternForCell(cell));
		}
		else {
			result.push_back(MapPatternType::FREE);
		}
	}
	return result;
}

MapPatternType MapMatchPattern::matchPatternForCell(Position& cell){
	auto arr = MapManager::instance().getNeighbours(cell, 1);
	std::vector<MapPatternData> patternCpy = patterns;

	for (auto rot = rotations.begin(); rot != rotations.end(); ++rot) {
		for (auto& pat : patternCpy) {
			int matchCounter = getNumberOfHitsForPattern(arr, pat);
			if (matchCounter == arr.size()) { // all targets match
				return getProperType(pat.type, *rot);
			}

			matTool.rotate90clockwise(pat.arr);
		}
	}
	return MapPatternType::FREE;
}

int MapMatchPattern::getNumberOfHitsForPattern(const Board& square, const MapPatternData& pat){
	int matchCounter = 0;
	for (auto it = square.begin(); it != square.end(); it++) {
		int indx = std::distance(square.begin(), it);
		if (pat.arr[indx] == 2) {  // without requirements
			matchCounter++;
		}
		else if (pat.arr[indx] == 0 && !it->isObstacle()) { // free required
			matchCounter++;
		}
		else if (pat.arr[indx] == 1 && it->isObstacle()) { //obstacle required
			matchCounter++;
		}
	}
	return matchCounter;
}

MapPatternType MapMatchPattern::getProperType(const MapPatternType type, const Rotation rot){
	if (rot == Rotation::DEG0) return type;
	MapPatternType temp = type;
	for (int i = 0; i < static_cast<int>(rot); i++) {
		temp = getNextTypeClockWise(temp);
	}
	return temp;
}

MapPatternType MapMatchPattern::getNextTypeClockWise(const MapPatternType type){
	switch (type)
	{
	case	MapPatternType::FREE:
		return type;

	case	MapPatternType::VERTICAL:
		return MapPatternType::HORIZONTAL;

	case	MapPatternType::HORIZONTAL:
		return MapPatternType::VERTICAL;

	case 	MapPatternType::CORNER_CONVEX_NE:
		return MapPatternType::CORNER_CONVEX_SE;

	case 	MapPatternType::CORNER_CONVEX_SE:
		return MapPatternType::CORNER_CONVEX_SW;

	case 	MapPatternType::CORNER_CONVEX_SW:
		return MapPatternType::CORNER_CONVEX_NW;

	case 	MapPatternType::CORNER_CONVEX_NW:
		return MapPatternType::CORNER_CONVEX_NE;

	case 	MapPatternType::CORNER_CONCAVE_NE:
		return MapPatternType::CORNER_CONCAVE_SE;

	case 	MapPatternType::CORNER_CONCAVE_SE:
		return MapPatternType::CORNER_CONCAVE_SW;

	case 	MapPatternType::CORNER_CONCAVE_SW:
		return MapPatternType::CORNER_CONCAVE_NW;

	case 	MapPatternType::CORNER_CONCAVE_NW:
		return MapPatternType::CORNER_CONCAVE_NE;

	default:
		break;
	}
	std::cout << "Error: Unsuported MapPatternType" << std::endl;
	return type;
}
