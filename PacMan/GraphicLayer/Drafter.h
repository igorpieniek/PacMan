#pragma once

#include "Position.h"
#include "Movement.h"
#include <string>
#include <vector>

class Drafter{
public:
	virtual void addImage(std::string path, Direction dir);
	virtual void draw(Position pos, Direction dir) = 0;
private:

	std::string filePath;
	Direction imageOriginalDirection;
	//Transformation trans;

};

