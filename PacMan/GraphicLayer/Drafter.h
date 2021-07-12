#pragma once

#include "Position.h"
#include "Movement.h"
#include <string>
#include <vector>

#include "Transformation.h"
#include "Texture.h"
#include "Render2D.h"

class Drafter{
public:
	virtual void addImage(std::string path, Direction dir);
	virtual void draw(Position pos, Direction dir);

protected:
	std::string filePath;
	Direction imageOriginalDirection;
	Transformation trans;
	std::shared_ptr<Texture> text;

};

