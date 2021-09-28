#pragma once
#include "Drafter.h"
#include "MapManager.h"
#include "Movement.h"
#include "MatrixTool.h"
#include "MapCreator.h"


class MapDrafter :public Drafter{
public:
	MapDrafter();
	void draw();
	void addImage(std::string path, Direction dir = Direction::EAST) override;

};

