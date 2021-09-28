#include "Astar.h"

bool Astar::calculate(int sizex, int sizey, std::vector<CellAstar>* map){
	try {
		parametersCheck(sizex, sizey, map);
		points = map;
		_sizex = sizex;
		_sizey = sizey;

		path.clear();

		resetPointsCategory();
		resetStopIterator();
		resetStartIterator();
		resetNotTestedVec();

		return main_process();
	}
	catch (std::exception& e) {
		std::cerr << e.what();
	}
	return false;
}

bool Astar::main_process(){
	BoardIter temp = startIter;
	while (temp != stopIter) { 

		if (notTested.empty()) {
			if (temp == startIter) {
				break;
			}
			temp->cat = AstarCellCategory::BLOCKED;
			temp = temp->parent_LastMove;
		}
		else {
			temp = getBestRatePoint();
		}

		if (temp->cat == AstarCellCategory::END)break;
		temp->cat = AstarCellCategory::BLOCKED; //changed status of point to "tested"

		notTested.clear();
		updateNeighbours(temp);
	}
	return dereferencePath();
}

bool Astar::dereferencePath(){
	BoardIter temp = stopIter;
	if (temp->parent == points->end()) return false;

	stopIter->cat = AstarCellCategory::END;
	startIter->cat = AstarCellCategory::START;

	while (temp != startIter) {
		path.push_back(temp);
		temp = temp->parent;
		temp->cat = AstarCellCategory::PATH;
	}
	path.push_back(startIter);
	startIter->cat = AstarCellCategory::START;
	return true;
}

void Astar::updateNeighbours(BoardIter& parent){
	bool firstIter = true;
	double min = 0;
	double currentRate = 0;
	for (const int& w: neighbourPointTrans) {
		for (const int& k : neighbourPointTrans) {
			if (!w && !k) continue; // parent point 
			if (!isDiagonalPathEnable && (w == k || w + k == 0)) continue;

			CellAstar neighbour{ parent->x + k, parent->y + w };
			auto neighbourIter = getPointIter(neighbour);

			if (!isNeighbourValid(neighbourIter)) continue;

			if (neighbourIter->cat == AstarCellCategory::EMPTY ||
				neighbourIter->cat == AstarCellCategory::END) {
				neighbourIter->parent = parent; //parent init
			}
			neighbourIter->cat = AstarCellCategory::AVAILABLE; // change neighbours category
			currentRate = calculate_rate(neighbourIter, parent);

			if (firstIter) {
				min = currentRate;
				firstIter = false;
			}
			if (currentRate <= min) {
				min = currentRate;
				neighbourIter->rate = currentRate;
				neighbourIter->parent_LastMove = parent;
				notTested.push_back(neighbourIter);
			}	
		}
	}
}

bool Astar::isNeighbourValid(BoardIter& it){
	return	(it != points->end() &&
			 it->cat != AstarCellCategory::OBSTACLE &&
			 it->cat != AstarCellCategory::BLOCKED);
}

double Astar::calculate_rate(BoardIter& nb, BoardIter& parent){
	double locRate = parent->rate + nb->distance(*stopIter);
	if (locRate < nb->rate) {
		nb->rate = locRate;
		nb->parent = parent;
	}
	return locRate;
}

BoardIter Astar::getPointIter(CellAstar& p){
	if (p.x < 0 || p.x >= _sizex ||
		p.y < 0 || p.y >= _sizey) return points->end();

	int position = p.x + (_sizex * p.y);
	if (position >= points->size()) return points->end();
	return points->begin() + position;
}

BoardIter Astar::getBestRatePoint(){
	std::vector<BoardIter>::iterator it = std::min_element(notTested.begin(), notTested.end(),
		[](const BoardIter& it1, const BoardIter& it2) {return it1->rate < it2->rate; });
	return *it;
}

void Astar::parametersCheck(int& sizex, int& sizey, std::vector<CellAstar>* map){
	if (map == nullptr) throw std::runtime_error("Empty pointer to map array ");
	if(map->size() != (sizex*sizey)) throw std::runtime_error("Wrong size parameters ");
}

void Astar::resetPointsCategory(){
	for (auto& cell : *points) {
		if (cell.cat == AstarCellCategory::AVAILABLE ||
			cell.cat == AstarCellCategory::BLOCKED ||
			cell.cat == AstarCellCategory::PATH) {

			cell.cat = AstarCellCategory::EMPTY;
		}
	}
}

void Astar::resetStopIterator(){
	//initilize stop point -> parent to points.end in case there is
	//no oppurtunity to gain the aim
	stopIter = std::find_if(points->begin(), points->end(),
		[](const CellAstar& pt) {return pt.cat == AstarCellCategory::END; });
	if (stopIter == points->end()) throw std::runtime_error("Something wrong with start point ");
	stopIter->parent = points->end();
	stopIter->parent_LastMove = points->end();
}

void Astar::resetStartIterator(){
	startIter = std::find_if(points->begin(), points->end(),
		[](const CellAstar& pt) {return pt.cat == AstarCellCategory::START; });
	if (startIter == points->end()) throw std::runtime_error("Something wrong with start point ");
	startIter->parent = points->end();
	startIter->parent_LastMove = points->end();
	startIter->rate = startIter->distance(*stopIter); //initialize start point rate and not tested vector
}

void Astar::resetNotTestedVec(){
	notTested.clear();
	notTested.push_back(startIter);
}

std::vector<BoardIter> Astar::getPath(){
	return std::move(path);
}
