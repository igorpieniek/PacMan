#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>



struct CellAstar;

using BoardIter = std::vector<CellAstar>::iterator;


enum class AstarCellCategory {
	EMPTY,
	OBSTACLE,
	START,
	END,
	PATH,
	AVAILABLE, /**< point consider as neigbour - on notTested list */
	BLOCKED,   /**< point already tested */

};


struct CellAstar {
	int x;
	int y;
	AstarCellCategory cat;
	double rate;
	BoardIter parent;
	BoardIter parent_LastMove;

	CellAstar();
	CellAstar(int xx, int yy, AstarCellCategory c = AstarCellCategory::EMPTY) : x(xx), y(yy), cat(c),
		rate(FLT_MAX),
		parent(BoardIter{}),
		parent_LastMove(BoardIter{}) {

	};
	double distance(const CellAstar& p2) {
		return sqrt(pow(p2.x - this->x, 2) + pow(p2.y - this->y, 2));
	}

	bool operator==(const CellAstar& p1) {
		return (this->x == p1.x) && (this->y == p1.y);
	}

};

class Astar{
public:

	bool calculate(int sizex, int sizey, std::vector<CellAstar>* map);
	std::vector<BoardIter> getPath();
	void enableDiagonalPath()  { isDiagonalPathEnable = true; };
	void disableDiagonalPath() { isDiagonalPathEnable = false; };

private:
	int _sizex{}, _sizey{};
	BoardIter startIter;
	BoardIter stopIter;
	std::vector<CellAstar>* points{nullptr};
	std::vector<BoardIter> notTested;
	std::vector<BoardIter> nb; //neighbours container
	std::vector<BoardIter> path;
	bool isDiagonalPathEnable = false;

	const std::vector<int> neighbourPointTrans{ -1, 0, 1 };

	bool main_process();
	bool dereferencePath();

	void updateNeighbours(BoardIter& parent);
	bool isNeighbourValid(BoardIter& it);
	double calculate_rate(BoardIter& nb, BoardIter& parent);
	BoardIter getPointIter(CellAstar& p);

	BoardIter getBestRatePoint();



	void parametersCheck(int& sizex, int& sizey, std::vector<CellAstar>* map);
	void resetPointsCategory();
	void resetStopIterator();
	void resetStartIterator();
	void resetNotTestedVec();



};
