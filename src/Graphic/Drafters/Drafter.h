#pragma once

#include "Position.h"
#include "Movement.h"
#include "MapManager.h"
#include <string>
#include <vector>
#include <unordered_map>

#include "Transformation.h"
#include "Texture.h"
#include "Render2D.h"



class Drafter {
public:
	virtual void addImage(std::string path, Direction dir = Direction::EAST);
	virtual void draw(Position pos, Direction dir = Direction::EAST);

protected:
	std::string filePath{};
	Direction imageOriginalDirection = Direction::EAST;
	Transformation trans{};
	std::shared_ptr<Texture> text{};

	static float scale;
	static Position correction;
	void calculateScale();
	void normalize(Position& pos);

	std::unordered_map<Direction, float> rotations = {
		{Direction::EAST,    0.0f},
		{Direction::SOUTH, -90.0f},
		{Direction::WEST,  180.0f},
		{Direction::NORTH,  90.0f}
	};


};



