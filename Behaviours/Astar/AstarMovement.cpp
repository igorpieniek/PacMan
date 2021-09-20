#include "AstarMovement.h"




AstarMovement::AstarMovement(CoordType speed, Position stopBase): stopPos(stopBase), stepSize(speed){
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
				if (path.size() != 0) {
					CoordType xdiff = pt->x - path.back().getX();
					CoordType ydiff = pt->y - path.back().getY();
					int maxcnt = (1/stepSize)-1;
					while (maxcnt > 0) {

						if (std::abs(xdiff) > std::abs(ydiff)) {
							if (xdiff > 0) {
								path.push_back({ path.back().getX() + stepSize, (float)pt->y });
							}
							else {
								path.push_back({ path.back().getX() - stepSize, (float)pt->y });
							}
						}
						else {
							if (ydiff > 0) {
								path.push_back({ (float)pt->x , path.back().getY() + stepSize });
							}
							else {
								path.push_back({ (float)pt->x , path.back().getY() + stepSize });
							}

						}
						--maxcnt;

					}
				}
				path.push_back({ (float)pt->x, (float)pt->y });
			}
			if (path.size() > 1) {
				currentPathExecIndx = path.size() - 1;
			}
		}
	}
	current = path[currentPathExecIndx];
	currentPathExecIndx--;


}

void AstarMovement::setStepResolution(CoordType res){
	stepSize = res;
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
