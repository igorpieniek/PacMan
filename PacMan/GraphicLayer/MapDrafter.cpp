#include "MapDrafter.h"



// 0 - means position free
// 1 - means obstacle
// 2 - means that it doesn't matter
// default oriantation - east
static const std::vector<MapPatternData> patterns = {
	{
		MapPatternType::STRAIGHT, 
		{1,1,2,
		 1,1,0,
		 1,1,2}
		},
	{
		MapPatternType::CORNER, // convex
		{1,1,2,
		 1,1,0,
		 2,0,0} 
		},
	{
		MapPatternType::CORNER, //concave
		{0,1,2,
		 1,1,1,
		 2,1,1}
		}
};

MapDrafter::MapDrafter(){

	cornerText   = std::make_shared<Texture>(turnPath);
	straightText = std::make_shared<Texture>(straightPath);

	map = MapManager::instance().getAllMap();


	for (auto& cell : map) {
		if (cell.isObstacle()) {
			PatternResult res = matchPattern(cell);
			if (res.isFound) {
				obstacles.push_back({ res.dir, res.cat, cell });
			}
		}
	}

}
void MapDrafter::draw(){
	for (auto it = obstacles.begin(); it != obstacles.end(); it++) {
		Position transCell = it->pos;
		normalize(transCell);
		trans.setRotation(rotations[it->dir]);
		trans.setTranslation(transCell.getX(), transCell.getY());
		trans.setScale(0.08f);
		if (it->type == MapPatternType::CORNER) {
			Render2D::instance().addToDraw(cornerText, trans);
		}
		else {
			Render2D::instance().addToDraw(straightText, trans);
		}
	}
	/*for (auto& cell : map) {
		if (cell.isObstacle()) {
			Drafter::draw(cell, Direction::EAST);
		}
	}*/
}

PatternResult MapDrafter::matchPattern(Position& cell){
	auto arr = MapManager::instance().getNeighbours(cell, 1);
	std::vector<MapPatternData> patternCpy = patterns;
	std::vector<Direction> dirs = { Direction::EAST, Direction::WEST, Direction::NORTH, Direction::SOUTH };
	MatrixTool<int> matTool;

	for (auto dir = rotations.begin(); dir != rotations.end(); ++dir) {
		for (auto& pat : patternCpy) {
			int matchCounter = 0;
			for (auto it = arr.begin(); it != arr.end(); it++) {
				int indx = std::distance(arr.begin(), it);
				if (pat.arr[indx] == 2) {  //neutral
					matchCounter++;
				}
				else if (pat.arr[indx] == 0 && !it->isObstacle()) {
					matchCounter++;
				}			
				else if(pat.arr[indx] == 1  &&  it->isObstacle()) { //match case
					matchCounter++;
				}
			}
			if (matchCounter == 9) {
				return { dir->first, pat.type, true };
			}

			matTool.rotate90clockwise(pat.arr);

		}
	}
	return { Direction::EAST, MapPatternType::STRAIGHT, false };
}

