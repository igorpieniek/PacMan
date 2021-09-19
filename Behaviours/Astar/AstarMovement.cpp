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
	// create path only once!
	// move using path
	static bool firstTime = true;
	if (firstTime) {
		firstTime = false;
		auto iter = std::find_if(map.begin(), map.end(),
			[&current](const CellAstar& cell) {return cell.x == current.getIntPos().getX() && cell.y == current.getIntPos().getY(); });
		if (iter != map.end()) iter->cat = AstarCellCategory::START;
		if (!astar.calculate(sizex, sizey, &map)) {
			std::cout << "Algorithm couldnt find the path to base" << std::endl;
		}
		else {
			for (const auto& pt : astar.getPath()) {
				path.push_back({ (float)pt->x, (float)pt->y });
			}
			if (path.size() > 2) {
				currentPathExecIndx = path.size() - 2;
			}
		}
	}

	//////////////
	if (currentPathExecIndx == 0) {} // do smth to inform that ghost is already in base OR  do nothing
	else if (current.getIntPos() == path[currentPathExecIndx]) {
		currentPathExecIndx--;
	}
	else {
		moveTool.moveInDir(current, getMoveDir(current.getIntPos(), path[currentPathExecIndx]));
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
