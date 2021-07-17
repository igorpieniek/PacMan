#include "MapDrafter.h"

MapDrafter::MapDrafter(){


	map = MapManager::instance().getAllMap();
	/*
	Movement moveTool;

	for (auto& cell : MapManager::instance().getAllMap()) {


		if (!cell.isObstacle()) {
			std::vector<Direction> allDirs = { Direction::EAST ,Direction::WEST, Direction::NORTH, Direction::SOUTH };

			Position cellPos = cell.getIntPos();
			auto possibilities = MapManager::instance().getAllPossibleDirections(cellPos);

			std::sort(allDirs.begin(), allDirs.end());
			std::sort(possibilities.begin(), possibilities.end());

			allDirs.erase(std::remove_if(allDirs.begin(), allDirs.end(),
				[&possibilities](Direction& dir) {return (std::find(possibilities.begin(), possibilities.end(), dir) != possibilities.end()); }));

			//if (MapManager::instance().isCorner(cellPos)) {

			//}
			for (auto& dir : allDirs) {
				Position toSave = cellPos;
				moveTool.moveInDir(toSave, dir);
				obstacles.push_back(ObstacleInfo{ getNextDirection(dir), toSave });
			}
		}
	}
	*/
}
void MapDrafter::draw(){
	for (auto& cell : map) {
		if (cell.isObstacle()) {
			Drafter::draw(cell, Direction::EAST);
		}
	}
}
