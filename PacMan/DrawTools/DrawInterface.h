#pragma once

#include "Position.h"
#include "Movement.h"

class DrawInterface{
public:
	virtual void setDirection(Direction dir) = 0;
	virtual void draw(Position& pos) = 0;
};

class DrawInterfaceFactory {
public:
	virtual std::shared_ptr<DrawInterface> getInstance() = 0;
};