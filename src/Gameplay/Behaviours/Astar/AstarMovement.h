#pragma once
#include "MoveAlgorithm.h"
#include "SafeMovement.h"
#include "MapManager.h"
#include "Astar/Astar.h"


class AstarMovement : public MoveAlgorithm {
public:
	AstarMovement(CoordType speed, Position stopBase);
	void update(Position& current) override;
	void setStepResolution(CoordType res) override;
	void reset()override {};
private:
	Astar astar{};
	Position stopPos{};
	std::vector<CellAstar> map{};
	std::vector<Position> path{};
	int currentPathExecIndx{};
	bool isPathCreated{ false };

	int sizex{}, sizey{};

	void createAstarMap();
	void calculateAndConvert(const Position& current);

};

