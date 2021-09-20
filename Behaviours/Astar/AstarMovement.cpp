#include "AstarMovement.h"




AstarMovement::AstarMovement(CoordType speed, Position stopBase): stopPos(stopBase), stepSize(speed){
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

	if (!isPathCreated) {
		isPathCreated = true;
		auto iter = std::find_if(map.begin(), map.end(),
			[&current](const CellAstar& cell) {return cell.x == current.getIntPos().getX() && cell.y == current.getIntPos().getY(); });
		if (iter != map.end()) iter->cat = AstarCellCategory::START;
		if (!astar.calculate(sizex, sizey, &map)) {
			std::cout << "Algorithm couldnt find the path to base" << std::endl;
		}
		else {
			auto pathRaw = astar.getPath();
			for (const auto& pt : pathRaw) {
				path.push_back({ (float)pt->x, (float)pt->y });
			}

			if (path.size() > 1) {
				currentPathExecIndx = path.size() - 1;
			}
			
		}
	}



	if (path.size() > 0 && currentPathExecIndx >= 0) {
		Direction dir = getMoveDir(current, path[currentPathExecIndx]);
		moveTool.moveInDir(current, dir);
		if (current == path[currentPathExecIndx]) {
			currentPathExecIndx--;
		}
	}



}

void AstarMovement::setStepResolution(CoordType res){
	stepSize = res;
	moveTool.setStepSize(res);
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
