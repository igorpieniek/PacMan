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
		{0,0,2,
		 0,1,1,
		 2,1,1} 
		},
	{
		MapPatternType::CORNER, //concave
		{1,1,1,
		 1,1,1,
		 1,1,0}
	}
};

MapDrafter::MapDrafter(){

	cornerText   = std::make_shared<Texture>(turnPath);
	straightText = std::make_shared<Texture>(straightPath);

	map = MapManager::instance().getAllMap();
	calculateScale();

	for (auto& cell : map) {
		if (cell.isObstacle()) {
			PatternResult res = matchPattern(cell);
			if (res.isFound ) {
				Position transCell = cell;
				normalize(transCell);
				Transformation tr;
				tr.setRotation(rotations[res.dir]);
				tr.setTranslation(transCell.getX(), transCell.getY());
				tr.setScale(0.08f);
				obstacles.push_back({ res.dir, res.cat, cell, tr });
			}
		}
	}

}
void MapDrafter::draw(){
	for (auto it = obstacles.begin(); it != obstacles.end(); it++) {
		if (it->type == MapPatternType::CORNER) {
			Render2D::instance().addToDraw(cornerText, it->trans);
		}
		else {
			Render2D::instance().addToDraw(straightText, it->trans);
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
	std::vector<Direction> dirs = {    Direction::NORTH,  Direction::WEST, Direction::SOUTH, Direction::EAST};
	MatrixTool<int> matTool;

	for (auto dir = dirs.begin(); dir != dirs.end(); ++dir) {
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
				else if(pat.arr[indx] == 1  &&  it->isObstacle()) { 
					matchCounter++;
				}
			}
			if (matchCounter == 9) {
				return { *dir, pat.type, true };
			}

			matTool.rotate90clockwise(pat.arr);
		}
	}
	return { Direction::EAST, MapPatternType::STRAIGHT, false };
}

