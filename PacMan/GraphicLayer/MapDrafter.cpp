#include "MapDrafter.h"

MapDrafter::MapDrafter(){

	cornerText   = std::make_shared<Texture>(turnPath);
	straightText = std::make_shared<Texture>(straightPath);

	map = MapManager::instance().getAllMap();
	std::vector<Position> testingMovements = {
		{1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}, {0,1}
	//    NE     E       SE     S        SW       W      NW     N
	};

	for (const auto& cell : map) {
		if (cell.isObstacle()) {
			int i = 0, startIndex = -1;
			std::vector<bool> neighStatus;
			for (auto testIt = testingMovements.begin(); testIt != testingMovements.end(); testIt++) {
				Position neighbour = cell;
				neighbour += *testIt;
				if (!MapManager::instance().isOccupied(neighbour)) {
					++i;
					neighStatus.push_back(true);
					continue;
				}
				neighStatus.push_back(false);
			}
			
			Direction dir;
			bool status = isStraight(dir, neighStatus);
			if (status) {
				obstacles.push_back({ dir, ObstacleType::STRAIGHT, cell });
			}
			/*
			if (i == 0) continue;

			if (i == 1) {
				if      (startIndex == 3 || startIndex == 7) obstacles.push_back({ Direction::EAST,  ObstacleType::STRAIGHT, cell });
				else if (startIndex == 1 || startIndex == 5) obstacles.push_back({ Direction::NORTH, ObstacleType::STRAIGHT, cell });
				else if (startIndex == 0 ) obstacles.push_back({ Direction::NORTH, ObstacleType::CORNER, cell });
				else if (startIndex == 2) obstacles.push_back({ Direction::EAST, ObstacleType::CORNER, cell });
				else if (startIndex == 4) obstacles.push_back({ Direction::SOUTH, ObstacleType::CORNER, cell });
				else if (startIndex == 6) obstacles.push_back({ Direction::WEST, ObstacleType::CORNER, cell });
			}
			*/

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
		if (it->type == ObstacleType::CORNER) {
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

bool MapDrafter::isStraight(Direction& result, std::vector<bool>& status){
	int i = 0;
	for (const auto& st : status) {
		if (st) ++i;
	}
	if (i == 0) return false;
	if (i == 1) {
		if		(status[3] || status[7]) { result = Direction::EAST; return true; }
		else if (status[1] || status[5]) { result = Direction::NORTH; return true; }
	}
	else if (i == 2) {
		int start = -1;
		for (auto it = status.begin(); it != status.end(); ++it) {
			if (*it) start = it - status.begin();
		}
		if      (start < 2)               { result = Direction::NORTH; return true; }
		else if (start >= 2 && start < 4) { result = Direction::EAST; return true; }
		else if (start >= 4 && start < 6) { result = Direction::NORTH; return true; }
		else if (start >= 6)              { result = Direction::EAST; return true; }
	}
	else if (i == 3) {
		if((status[0] && status[1] && status[2]) ||
		   (status[4] && status[5] && status[6])) {
			result = Direction::NORTH; return true;
		}
		else if ((status[2] && status[3] && status[4]) ||
			     (status[6] && status[7] && status[0])) {
			result = Direction::EAST; return true;
		} 
	}
	return false;
}

bool MapDrafter::isCorner(Direction& result, std::vector<bool>& status){

	return false;
}
