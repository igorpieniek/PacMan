#pragma once

#include "MapManager.h"
#include "Mediator.h"
#include "CellPoint.h"
#include "ConfigLoader.h"
#include <vector>

class PointsManager: public GameMediatorComponent{
public:
	PointsManager(int specialAmount);
	int getPoints()const { return currentPoints; };
	bool isAllPointsReached()const;

	void notify(Event evt) override;
	void notifyPlayerPosition(const Position& pos) override;

	const std::vector<CellPoint>& getPointsData()const { return cellPoints; };
	
private:
	int currentPoints{};
	int specialPointsAmount{};
	int firstPointVal = 0;
	bool lockPlayerPosNotify = false;
	std::vector<CellPoint> cellPoints;

	using CellPointIter = std::vector<CellPoint>::iterator;

	void createCellPointArray();
	void addPoints(CellPointIter& it);
	void removeCellPoint(CellPointIter& it);
	void checkSpecialPoint(CellPointIter& it);
	CellPointIter getCellPointIter(const Position& pos);

};

