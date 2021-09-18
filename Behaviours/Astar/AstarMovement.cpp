#include "AstarMovement.h"

AstarMovement::AstarMovement(CoordType speed, Position stopBase): stopPos(stopBase){
	moveTool.setStepSize(speed);
	sizex = static_cast<int>(MapManager::instance().getMapXSize());
	sizey = static_cast<int>(MapManager::instance().getMapYSize());
	map.reserve(sizex*sizey);
	createAstarMap();
	astar.disableDiagonalPath();

}

void AstarMovement::update(Position& current){
	//update startPos on map 
	// calculate new path only if it gets to int pos
	if (!astar.calculate(sizex, sizey, &map)) {
		std::cout << "Algorithm couldnt find the path to base" << std::endl;
	}
}

void AstarMovement::setStepResolution(CoordType res)
{
}

void AstarMovement::createAstarMap(){
	for (const auto& cell : MapManager::instance().getAllMap()) {
		AstarCellCategory cat = AstarCellCategory::EMPTY;
		if (cell.isObstacle()) {
			cat = AstarCellCategory::OBSTACLE;
		}
		else if (static_cast<Position>(cell) == stopPos) {
			cat = AstarCellCategory::END;
		}
		map.push_back({ (int)cell.getX(), (int)cell.getY(), cat });
	}

}
